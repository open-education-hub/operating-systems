# `apache2` Document Root

## Question Text

What is the document root of the `apache2` server?

## Question Answers

- `/etc/apache2`

+ `/usr/local/apache2/htdocs/`

- `/var/www/html`

- `/var/www/apache2/htdocs`

## Feedback

In `strace` we see that the server opens the file `/usr/local/apache2/htdocs/index.html`.
This means that the document root is `/usr/local/apache2/htdocs/`.
