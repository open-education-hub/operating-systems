# Operating Systems (OER)

[![copying.md](https://img.shields.io/static/v1?label=license&message=CCBY-SA4.0&color=%23385177)](https://github.com/open-education-hub/operating-systems/blob/master/COPYING.md)
[![copying.md](https://img.shields.io/static/v1?label=license&message=BSD-3-clause&color=%23385177)](https://github.com/open-education-hub/operating-systems/blob/master/COPYING.md)
[![discord](https://img.shields.io/badge/users-93-7589D0?logo=discord)](www.bit.ly/OpenEduHub)
[![contributors](https://img.shields.io/github/contributors/open-education-hub/operating-systems)](https://github.com/open-education-hub/operating-systems/graphs/contributors)
[![reddit](https://img.shields.io/reddit/subreddit-subscribers/OpenEducationHub?style=social)](https://www.reddit.com/r/OpenEducationHub/)
[![twitter](https://img.shields.io/twitter/url?style=social&url=https%3A%2F%2Ftwitter.com%2FOpenEduHub)](https://twitter.com/OpenEduHub)
[![youtube](https://img.shields.io/youtube/channel/views/UCumS6d-kaVXreY46eZLtEvA?style=social)](https://www.youtube.com/@OpenEduHub/)

These are open educational resources ([OER](https://en.wikipedia.org/wiki/Open_educational_resources)) for Operating Systems classes.
They are to be used by teachers, trainers, students and hobbyists who want to learn about modern topics in operating systems.

## Using the Content

Content is located in the `content/` folder.
It currently consists of 5 chapters:

* [Software Stack](content/chapters/software-stack/)
* [Data](content/chapters/data/)
* [Compute](content/chapters/compute/)
* [Input/Output](content/chapters/io/)
* [Application Interaction](content/chapters/app-interact/)

Each chapter has its own folder.
Content for each chapter is split in two subfolders:

* `lecture/`: content to be presented and discussed as part of lectures
* `lab/`: content to be worked on as practical activities during labs / seminars

Lecture content is expected to be presented and followed.
Lab content is expected to be used as practice work.

## Chapter Contents

Lecture content consists of slides and demos.
Slides are written in [GitHub Markdown](https://guides.github.com/features/mastering-markdown/) and use [reveal-md](https://github.com/webpro/reveal-md) and [reveal.js](https://revealjs.com/) to render HTML output.
Lecture slides are built from the `slides.md` file using the `make` command (and the `Makefile`).
Demos are snippets of code and support files that showcase concepts and ideas related to the lecture.
Demos are located in the `demo/` folder.
Each demo has its own folder with source code, `Makefile` or other build files (if required) and support files.

Lab content consists of lab text and lab activities.
Lab text is placed in the `README.md` file.
Each lab activity has its own folder with source code, `Makefile` or other build files (if required) and support files.

## Contributing

Contributions are welcome.
See the [contribution guide](CONTRIBUTING.md) on how you could report or fix issues and on how you can improve the content.

Reviewers are requested to follow the [reviewing guide](REVIEWING.md).
