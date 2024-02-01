Example of config file:
```toml
error_page = { 404 = "/path/to/404.html" }
client_max_body_size = "10MB"

[[server]]
host = "127.0.0.1"
port = 8080
server_name = [ "example.com", "www.example.com" ]

	[[server.route]]
	path = "/"
	allowed_methods = [ "GET", "DELETE" ]
	root = "/var/www/html"
	autoindex = false
	index = "index.html"
	cgi_extensions = [ ".php", ".cgi" ]
	response_header = { Server = "Webserv" }

	[[server.route]]
	path = "/upload"
	allowed_methods = [ "POST" ]
	upload_path = "/var/uploads"

	[[server.route]]
	path = "/old-page"
	redirect = "/new_page"
```