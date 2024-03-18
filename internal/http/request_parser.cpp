#include "request_parser.hpp"
#include "method.hpp"
#include <regex>

Result<Request, std::string>
RequestParser::parseRequest(const std::string &request_line, const std::vector<std::string> &headers, const Option<std::string> &body) {
    // TODO: parse query
    const Result<RequestParser::RequestLine, std::string> parse_request_line_result = parseRequestLine(request_line);
    if (parse_request_line_result.isErr()) {
        return Err(parse_request_line_result.unwrapErr());
    }
    const RequestLine parsed_request_line = parse_request_line_result.unwrap();

    std::map<std::string, std::string> parsed_headers;
    for (std::size_t i = 0; i < headers.size(); i++) {
        const Result<std::pair<std::string, std::string>, std::string> parse_header_field_result = parseHeaderFieldLine(headers[i]);
        if (parse_header_field_result.isErr()) {
            return Err(parse_header_field_result.unwrapErr());
        }
        const HeaderField header_field = parse_header_field_result.unwrap();
        parsed_headers.insert(header_field);
    }

    // TODO: pass HTTP-version
    return Ok(Request(
            parsed_request_line.first.first,
            parsed_request_line.first.second,
            std::map<std::string, std::string>(),
            parsed_headers,
            body.unwrapOr("")));
}

// field-line = field-name ":" OWS field-value OWS
Result<std::pair<std::string, std::string>, std::string>
RequestParser::parseHeaderFieldLine(const std::string &line) {
    // : の前後で区切る
    const std::size_t colon_pos = line.find(':');
    if (colon_pos == std::string::npos) {
        return Err<std::string>("invalid field-line");
    }
    const std::string raw_field_name = line.substr(0, colon_pos);
    const std::string raw_field_value = line.substr(colon_pos + 1);

    // field-name の検証
    /*
     * field-name = token
     * token = 1*tchar
     * tchar = "!" / "#" / "$" / "%" / "&" / "'" / "*"
     *       / "+" / "-" / "." / "^" / "_" / "`" / "|" / "~"
     *       / DIGIT / ALPHA ; any VCHAR, except delimiters
     */
    // TODO: 正規表現をやめる
    std::regex re_field_name("^[!#$%&'*+\\-\\.\\^_`\\|~0-9A-Za-z]+$");
    if (!std::regex_match(raw_field_name, re_field_name)) {
        return Err<std::string>("invalid field-name");
    }

    // field-value の検証
    // OWS = *( SP / HTAB ) で trim する
    /* (RFC 9110)
     * A field value does not include leading or trailing whitespace.
     * When a specific version of HTTP allows such whitespace to appear in a message,
     * a field parsing implementation MUST exclude such whitespace
     * prior to evaluating the field value.
     */
    const std::string::size_type begin = raw_field_value.find_first_not_of(" \t");
    const std::string::size_type end = raw_field_value.find_last_not_of(" \t");
    if (begin == std::string::npos || end == std::string::npos) {
        return Err<std::string>("invalid field-value");
    }
    const std::string trimmed_raw_field_value = raw_field_value.substr(begin, end - begin + 1);

    /*
     * field-value = *field-content
     * field-content = field-vchar [ 1*( SP / HTAB / field-vchar ) field-vchar) ]
     * field-vchar = VCHAR / obs-text
     * obs-text = %x80-FF
     */
    // trim 済みなので, *( SP / HTAB / field-vchar ) であることを確認すればよい
    // TODO: 正規表現をやめる
    std::regex re_field_value("^[\\x21-\\x7E\\x80-\\xFF \t]+$");
    if (!std::regex_match(trimmed_raw_field_value, re_field_value)) {
        return Err<std::string>("invalid field-value");
    }

    return Ok(std::make_pair(raw_field_name, trimmed_raw_field_value));
}

// request-line = method SP request-target SP HTTP-version
// NOTE: サーバーは SP 以外にも HTAB, VT, FF, CR を区切りとしてもよい (MAY)
Result<RequestParser::RequestLine, std::string> RequestParser::parseRequestLine(const std::string &line) {
    // TODO: 正規表現をやめる
    std::regex re("^([^ ]+) ([^ ]+) (HTTP/\\d\\.\\d)$");
    std::smatch match;
    if (!std::regex_match(line, match, re)) {
        return Err<std::string>("invalid request-line");
    }

    const HttpMethod method = httpMethodFromString(match[1].str());
    if (method == kMethodUnknown) {
        return Err<std::string>("unknown method");
    }
    const std::string request_target = match[2].str();
    const std::string http_version = match[3].str();

    return Ok<RequestLine>(std::make_pair(std::make_pair(method, request_target), http_version));
}
