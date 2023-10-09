#! /usr/bin/python3

from argparse import ArgumentParser
from os import path
import re


MEDIA_URL = "!\[.*\]\(\.\./media/.*\)\n"
MEDIA_URL_HTML = "<img.*src=\"\.\./media/.*\".*/>\n"


def process_media_link(line, filename, split_token, url_regex, split_char):
    if not re.fullmatch(url_regex, line):
        return line

    parts = line.split(split_token)
    if len(parts) != 2:
        return line

    media_path = parts[1].strip(split_char).split("/")
    if media_path[0] != ".." and media_path[1] != "media":
        return line

    new_path = path.join(filename.split("/")[0], *media_path[1:])

    return parts[0] + split_token + new_path


def expand_if_media_link(line, filename):
    if line[0] == "!":
        return process_media_link(line, filename, "](", MEDIA_URL, ")")
    elif line[0] == "<":
        return process_media_link(line, filename, "src=\"", MEDIA_URL_HTML, "/")
    else:
        return line


def main():
    parser = ArgumentParser()
    parser.add_argument('--input', required=True,
        help='Markdown file containing includes that need expanding')
    parser.add_argument('--output', required=True,
        help='Markdown file to expand the input to')
    args = parser.parse_args()

    with open(args.input, 'r') as f:
        lines = f.readlines()

    f = open(args.output, 'w')
    for line in lines:
        if not line.startswith('!INCLUDE'):
            f.write(line)
            continue

        _, filename = line.split()
        filename = filename.removeprefix('"').removesuffix('"')
        filename = path.join(path.dirname(args.input), filename)

        include_file = open(filename, 'r')
        for inc_line in include_file.readlines():    
            f.write(expand_if_media_link(inc_line, filename))


if __name__ == '__main__':
    main()
