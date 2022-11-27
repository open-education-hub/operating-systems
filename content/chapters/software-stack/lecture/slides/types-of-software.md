---

## Types of Software

----

### Usable vs Reusable

* Software provides features by extending hardware
* Features are used by:
  * users (as interactive applications / processes)
  * system (as non-interactive services / processes)
  * other applications (as reusable libraries)
* Software components
  * Applications: usable
  * Libraries: reusable

----

### Applications

![Applications](media/applications.svg)

----

### Libraries

![Libraries](media/libraries.svg)

----

### Application Software and System Software

![Application and System Software](media/application-system-software.png)
<!-- https://www.webopedia.com/definitions/systems-software/ -->

----

### Libraries and Frameworks

![Libraries and Frameworks](media/libraries-frameworks.png)
<!-- https://medium.com/@MarcStevenCoder/build-reusable-frameworks-809438ef46e7 -->

----

### Applications and Libraries

Common features / attributes

* machine / binary code (for compiled programs)
* data and instructions sections (`rodata`, `data`, `bss`, `text`)
* stored as files in the filesystem

----

### Applications vs Libraries

| Applications                     | Libraries                                  |
| :------------------------------: | :----------------------------------------: |
| entry point (`main`, `_start`)   | exposed interface (API)                    |
| usable                           | reusable                                   |
| load-time                        | link-time and load-time                    |
| used by system and user          | used by other applications or libraries    |
