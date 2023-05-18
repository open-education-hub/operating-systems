/*
 * Test HTTP parser: get request path from HTTP request header.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "http_parser.h"

#ifndef BUFSIZ
#define BUFSIZ		8192
#endif

static char *simple_request = "GET /state/thy/bidding.html HTTP/1.0\r\n"
			       "\r\n";

static char *complex_request = "GET /all/for/the/empire.html HTTP/1.1\r\n"
			       "User-Agent: curl/7.18.0 (i486-pc-linux-gnu) libcurl/7.18.0 OpenSSL/0.9.8g zlib/1.2.3.3 libidn/1.1\r\n"
			       "Host: 0.0.0.0=5000\r\n"
			       "Accept: */*\r\n"
			       "\r\n";

static http_parser request_parser;
static char request_path[BUFSIZ];	/* storage for request_path */


/*
 * Callback is invoked by HTTP request parser when parsing request path.
 * Request path is stored in global request_path variable.
 */

static int on_path_cb(http_parser *p, const char *buf, size_t len)
{
	assert(p == &request_parser);
	memcpy(request_path, buf, len);

	return 0;
}

/* Use mostly null settings except for on_path callback. */
static http_parser_settings settings_on_path = {
	/* on_message_begin */ 0,
	/* on_header_field */ 0,
	/* on_header_value */ 0,
	/* on_path */ on_path_cb,
	/* on_url */ 0,
	/* on_fragment */ 0,
	/* on_query_string */ 0,
	/* on_body */ 0,
	/* on_headers_complete */ 0,
	/* on_message_complete */ 0
};

/*
 * Call http_parser to parse sample_request. Subsequently print request_path
 * as filled by callback.
 * Callback is on_path_cb as setup in settings_on_path.
 */

int main(void)
{
	size_t bytes_parsed;

	/* init HTTP_REQUEST parser */
	http_parser_init(&request_parser, HTTP_REQUEST);

	bytes_parsed = http_parser_execute(&request_parser, &settings_on_path, simple_request, strlen(simple_request));
	printf("Parsed simple HTTP request (bytes: %lu), path: %s\n", bytes_parsed, request_path);

	/* init HTTP_REQUEST parser */
	http_parser_init(&request_parser, HTTP_REQUEST);

	bytes_parsed = http_parser_execute(&request_parser, &settings_on_path, complex_request, strlen(complex_request));
	printf("Parsed complex HTTP request (bytes: %lu), path: %s\n", bytes_parsed, request_path);

	return 0;
}
