# Resources and Useful Links

## Need to Know

List of resources:

- [GitHub Repository](https://github.com/cs-pub-ro/operating-systems)
- [Moodle Class](https://curs.upb.ro/2023/course/view.php?id=7774) (used for homework submissions, quizzes, announcements, etc.)
- [Teams Class](https://teams.microsoft.com/l/team/19%3aLTQa0tGvTM_L1c8N9F_dwZJ8RKLA_KqVejJJdeLfHos1%40thread.tacv2/conversations?groupId=ca6de354-95d1-4b60-9668-d79997e9d058&tenantId=2d8cc8ba-8dda-4334-9e5c-fac2092e9bac)
- [Rules and Grading](https://cs-pub-ro.github.io/operating-systems/rules-and-grading)
- [Books / Reading Materials](http://elf.cs.pub.ro/so/res/doc/) (you will need to log in using your `UPB` account)
- [OS Calendar](https://calendar.google.com/calendar/u/0/embed?src=d2biu4r5gcv83ndamn6tpe0onc@group.calendar.google.com&ctz=Europe/Bucharest)
- [OS Course Planning](https://docs.google.com/spreadsheets/d/1HVCP7ybjrtrtN5MMQYbSnvHoals5IbagtY1SaG9K3FE/edit?usp=sharing)

## Documentation and Reading Materials

You can find the documentation for the operating systems course at [this address](http://elf.cs.pub.ro/so/res/doc/).
You will need to log in using the `UPB` institutional account.

## Calendar

There are no classes / labs in the 27 November 2023 - 1 December 2023 week.

You can find the full calendar in multiple formats below:

- Calendar ID: `d2biu4r5gcv83ndamn6tpe0onc@group.calendar.google.com`
- [XML](http://www.google.com/calendar/feeds/d2biu4r5gcv83ndamn6tpe0onc%40group.calendar.google.com/public/basic)
- [ICAL](http://www.google.com/calendar/ical/d2biu4r5gcv83ndamn6tpe0onc%40group.calendar.google.com/public/basic.ics)
- [HTML](http://www.google.com/calendar/embed?src=d2biu4r5gcv83ndamn6tpe0onc%40group.calendar.google.com&ctz=Europe/Bucharest)

You can also find the course planning [here](https://docs.google.com/spreadsheets/d/1HVCP7ybjrtrtN5MMQYbSnvHoals5IbagtY1SaG9K3FE/edit?usp=sharing).

## Virtual Machine

You can use any Linux environment (native install, `WSL`, virtual machine, docker environment, etc.) for the OS class.
We provide Linux virtual machines with all the setup ready.

### VirtualBox / VMware

You can download the Linux virtual machine from [this link](https://repository.grid.pub.ro/cs/so/linux-2024/so-vm.ova).
You will need to log in using your `UPB` account.

You can import the `.ova` file in [VirtualBox](https://www.virtualbox.org/) or [VMware](https://www.vmware.com/).
Follow the instructions on the official websites for installation.

### UTM (macOS >= 11)

If you are using an `M1` Apple system, you will not be able to run the virtual machine using VirtualBox or VMware.
You will need to use [`UTM`](https://mac.getutm.app/), along with a [`.qcow2`](https://repository.grid.pub.ro/cs/so/linux-2024/SO-Ubuntu-22-04-03-LTS.utm.zip) image.
You will need to log in using your `UPB` account.

After you install `UTM` and download and unzip the archive, you can import it using the `Open existing VM` option in `UTM`.

You can also follow the instructions for [running the VM using `qemu`](https://github.com/cs-pub-ro/operating-systems/blob/main/util/macos-vm/README.md).
