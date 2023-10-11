# Rules and Grading

## Grading

To pass this course you need to obtain  **4.5 points** from a total of **11 points**:

- 4 points for the [exam](#exam-4-points)
- 5 points for [assignments](#assignments-5-points)
- 1 point for [laboratory sessions](#laboratory-sessions-1-point)
- 1 point for [lecture quizzes](#lecture-quizzes-1-point)

### Exam (4 points)

The exam covers the entire course material and takes place in person.
Students can take part in one exam per session.
They must present the student ID card or a photo ID for identification.

**Passing the course requires obtaining a minimum of 2 out of 4 points (i.e., 50%) of the exam score.**

#### Exam Structure

The exam consists of two components:

1. Interview
   - It lasts **15 minutes for each student**.
   - There are typically two sessions of 120 minutes (8 students each):
     - 09:00-11:00
     - 11:30-13:30
   - It is **open book**, you can use written materials.
   - Students will be given a slot and be announced prior to the exam.
   - Each student will be asked questions will be graded based on provided answers.
   - The maximum score is 11 (out of 10), with 1 point as a bonus.
   - This component accounts for **70% of the total exam score**, which is **2.8 out of the total 4 points**.
   - The oral exam will be recorded internally.

1. Relevance quiz
   - It lasts **20 minutes**.
   - This part is also **open-book**, meaning you can use written materials and offline resources.
     However, Internet access will not be allowed.
   - All students scheduled for the exam in the same day will take this component at the same time, usually 11:00-11:30.
   - It will be conducted on [Moodle](https://curs.upb.ro/2023/course/view.php?id=7774).
   - You will receive **11 True/False questions** that require explanations.
     **You will receive 0 points if you choose the right answer, but the explanation is wrong.**
   - The maximum score is 11 (out of 10), with 1 point as a bonus.
   - This component accounts for **30% of the total exam score**, which is **1.2 out of 4 points**.

The total points are truncated to **4 points**.

#### Exam Simulation

An oral exam simulation will be organized on **Saturday, January 20, 2024, at 15:00 EET**, online, on Microsoft Teams, and it will be recorded.
It will last for **2 hours** and will involve **8 students** that volunteer (first-come, first-served) to take part in the exam simulation.
All students and members of the team can participate, but only 8 students will be examined, while the others will observe.
The exam simulation will be recorded.

The simulation will focus on the interview component of the exam.
Students who participate in the simulation can choose to keep their score or retake the interview component during the actual exam session.

The announcement for the exam simulation will be posted one week prior to its scheduled date, and students can enroll by replying within that thread.
Similarly, another announcement will follow the simulation, offering students the option to retain their scores.

#### Recommendations

- Go through the [Student's Guide](https://docs.google.com/document/d/1VRRkYKcMHCKX7oRJqx3QHZh5PN0ph05I9ZJxaOBaR8Y/edit?usp=sharing).
- For the interview component, review the [list of questions](https://docs.google.com/document/d/1gkZzAfK11bV7U2bg7C3OJe4t2TdHlcbBuGnbJBJKbKQ/edit#heading=h.ydgbek8rdeos) that serves as a starting point for the interview.
- Watch the exam simulation to see how the interview will be conducted.

#### Resources

1. [Recordings OS 2022-2023 3CC](https://ctipub.sharepoint.com/sites/03acsla3s2socacbcc/Shared%20Documents/Forms/AllItems.aspx?RootFolder=%2Fsites%2F03acsla3s2socacbcc%2FShared%20Documents%2FCurs%203CC%2FRecordings&FolderCTID=0x012000E35B9BA594DFDC438C2F7EEFC2BA28C1)
1. [OS oral exam simulation 2022-2023](https://ctipub.sharepoint.com/sites/03acsla2s1socacbcccd/_layouts/15/stream.aspx?id=%2Fsites%2F03acsla2s1socacbcccd%2FShared%20Documents%2FGeneral%2FRecordings%2FSO%202022%2D2023%20%2D%20Simulare%20examen%20oral%2D20230121%5F165841%2DMeeting%20Recording%2Emp4&ga=1)
1. [Relevance quiz example](https://curs.upb.ro/2023/mod/quiz/view.php?id=42286)
1. [Lecture notes](https://drive.google.com/drive/folders/1T08PmJ_fKTA8FLHvhXYw33CBK6D0QPpR?usp=drive_link)

### [Assignments](https://cs-pub-ro.github.io/operating-systems/Assignments/) (5 points)

Assignments are worth **5 points** of the final grade.
However, you can get as much as **10 points** in total.
There are 3 assignments, followed by 2 bonus ones, graded as follows:

1. Assignment 1: 1.66 points
1. Assignment 2: 1.66 points
1. Assignment 3: 1.66 points
1. Bonus Assignment 1: 2.5 points
1. Bonus Assignment 2: 2.5 points

The score from the bonus assignments can make up for any points lost on the other assignments.
Points past **5 points** can be used to make up points for [Laboratory Sessions](#laboratory-sessions-1-point) or [Lecture Quizzes](#lecture-quizzes-1-point).

**Each assignment has a single deadline.**
**Once the deadline passes, the assignment can no longer be submitted.**

Each assignment solution submission gets a maximum of **100 assignment points**.
These are comprised of:

- **90 points** for the correct implementation of the assignment
- **10 points** for coding style

Both components are verified and graded automatically by the assignment checker system: automated tests for the implementation, linters and build output analysis for coding style.
The assignment checker system presents the final grade.
Coding style points are only provided if the assignment solution submission gets at least **60 points** for the correct implementation.

However, **there may be exceptional cases in which this grading scheme is not followed**, for example, if the assignment is implemented only to pass the tests and does not meet the assignment requirements.
Exceptional cases may include instances of deadlock, incorrect synchronizations between processes/threads, races (whether they are manifested or not), and other unspecified but deemed inappropriate situations.

Please use the automatic verification system to check the proper compilation and execution of assignments and report any issues promptly.

Assignments will be subject to [plagiarism detection and penalties](#plagiarism-penalties).

### Assignment Deadline

Each assignment comes with a deadline for completion.
**After the deadline expires, the assignment can no longer be submitted.**
Assignments cannot be submitted during the summer or inter-semester break.

#### No Exam For Assignment Heroes

Those who receive at least **9 points** (out of the total of **10 points**), will not be required to be part of and pass the exam.
In exceptional circumstances, when there is doubt on the correctness of getting the **9 points**, the student will still be request to be part of the exam.

#### Solving and Submitting Assignments

Assignments are solved and submitted via [GitLab](https://gitlab.cs.pub.ro/operating-systems).
See the `README.checker.md` file of each assignment repository for details.

The high-level steps are:

1. Make a **private** fork of the assignment repository on [GitLab](https://gitlab.cs.pub.ro/operating-systems).
1. Clone the fork locally.
1. Create a branch for the solution (e.g. a branch named `solution`).
1. Solve the assignment.
   Do periodic commits while solving.
   Do periodic pushes to your **private** fork.
1. Use the `local.sh` script to build the Docker environment and to check / grade the assignment solution.
1. Do a final push.
   See the automatic checking on the Jobs entry on GitLab for your fork.
1. Configure Moodle to retrieve the submissions for GitLab, or do a Moodle archive submission of your assignment solution.

### [Laboratory Sessions](https://cs-pub-ro.github.io/operating-systems/Lab/) (1 point)

Each lab is graded between **0 and 12 points** and the final grade is calculated by summing up all scores and dividing to the number of labs.
The lab score is truncated at **10 lab points** (corresponding to the **1 course point** allocated for the lab).

The grade for each lab is composed of the following components:

- 3 points for a **lab quiz**, which includes 4 questions: 2 questions from the preceding lab and 2 from the current one.
  One question acts as a bonus question.
- 2 points for involvement
  They are awarded by the TA according to their own criteria: interesting questions, good answers, solving bonus tasks, helping other students, etc.
- 3 points for completing the **basic exercises** of the laboratory
- 2 points for completing the **advanced exercises** of the laboratory
- 2 points for **bonus activity** during the laboratory.

If you miss a lab or do not receive the maximum score on other labs, the lab bonuses will assist you in improving your final grade.
**You can recover up to 2 missed labs with the agreement of the lab assistant.**

**Collaboration during lab sessions is strongly encouraged.**

### Lecture Quizzes (1 point)

To reinforce knowledge, there will be 4 multiple-choice quizzes as follows:

1. Quiz 1 - covering questions from the [Software Stack chapter](https://cs-pub-ro.github.io/operating-systems/Lecture/Software%20Stack/), will take place on the following dates:

    - Series CA: 17.10.2023
    - Series CB: 18.10.2023
    - Series CC: 17.10.2023
    - Series CD: 17.10.2023

1. Quiz 2 - covering questions from the [Data chapter](https://cs-pub-ro.github.io/operating-systems/Lecture/Data/), will take place on the following dates:

    - Series CA: 07.11.2023
    - Series CB: 08.11.2023
    - Series CC: 07.11.2023
    - Series CD: 07.11.2023

1. Quiz 3 - covering questions from the [Compute chapter](https://cs-pub-ro.github.io/operating-systems/Lecture/Compute/), will take place on the following dates:

    - Series CA: 05.12.2023
    - Series CB: 06.12.2023
    - Series CC: 05.12.2023
    - Series CD: 05.12.2023

1. Quiz 4 - covering questions from the [I/O chapter](https://cs-pub-ro.github.io/operating-systems/Lecture/IO/), will take place on the following dates:

    - Series CA: 09.01.2024
    - Series CB: 10.01.2024
    - Series CC: 09.01.2024
    - Series CD: 09.01.2024

Lecture quizzes are closed-book.
They take place on the [Moodle platform](https://curs.upb.ro) at the beginning of the corresponding lectures.
Each quiz lasts **5 minutes**.
Each quiz consists of **5 multiple-choice questions** with a single answer option.
Each quiz is worth **0.3 points of the final grade**.
Lecture quiz grade is truncated at **1 point**.

## Rules

### Checking Assignments

Assignments will be automatically checked using public tests.

### Solving Assignments

Assignments will be completed using the C programming language, which is generally used in the implementation of an operating system and its functionalities.

Operating Systems assignments are individual.
Each assignment should be completed by a student without consulting the source code of their peers.

We understand that teamwork is essential, but we do not have the environment for team projects in the Operating Systems course.
However, we offer the possibility to equate one or two assignments for additional technical activities, which are likely to involve teamwork.

If you encounter any problems in solving an assignment, please use the forum dedicated to that assignment.
You can ask the lab assistants or the course teacher, but **it is desirable to post your questions on the forum** to be seen by as many students as possible and to help as many students as possible.

You can discuss among yourselves within the bounds of common sense;
in other words, you don't have to dictate the solution to someone, but you can provide a general idea.
It is not allowed to request the solution to an assignment on sites like [StackExchange](https://stackexchange.com/) or others.
You can ask more general questions, but do not request the assignment solution.

You can use code from labs and skeletons provided by us without any issues.
You can use external resources ([GitHub](https://github.com/), open-source code, or others) as long as they do not represent obvious assignment solutions, publicly posted with or without intent.
See the next paragraph for clarification.

It is not allowed to publish assignment solutions (even after the course has ended).
If you find public assignment solutions on GitHub or elsewhere, do not consult them, as this could lead to plagiarism and loss of points on assignments.
We reiterate that if you need clarification, please use the forums provided for each assignment.

It is not allowed to transfer files among yourselves.
In general, we recommend not sharing screens with other classmates, either for inspiration or to help them with a solution.
Avoid testing an assignment on a classmate's system.
There can be exceptions, such as assisting someone with troubleshooting, but please be mindful not to transition from "let's figure out the problem" to "let me solve your assignment."
We recommend using the dedicated forum for each assignment to ask questions (or any other channel provided to you).

### Plagiarism Penalties

Generally, we consider punitive measures to be the last resort.
As long as an assignment is completed individually without problematic source code contributions from external sources, it is not considered a copied assignment.

The concept of plagiarized assignments includes, but is not limited to, situations such as:

- Two assignments that bear sufficient resemblance to draw this conclusion.
- Using source code from the internet that is clearly the solution to the assignment.
- Utilizing portions of another classmate's code.
- Accessing another classmate's code during the assignment.
- Modifying an existing assignment.
- Tracing another classmate's code.
- Direct assistance in completing the assignment (someone else wrote or dictated the code).
- Someone else completes the assignment (willingly, for payment, or other benefits).

In the event that two assignments are deemed plagiarized, both the source and destination will receive identical penalties, without discussions regarding who copied from whom and whose fault it is.

Copying any part of an assignment results in the entire assignment's score being voided.
**Any assignment submitted (before or after the plagiarized assignment) in the same academic session receives a score of 0 and is not eligible for resubmission within the current academic year.**

We emphasize that our goal is not and will not be to penalize plagiarism.
We view plagiarism as a dishonest act that will be punished if it occurs.
Our objective, however, is to prevent plagiarism, and to achieve this, we provide support and resources from our team in all their forms.

### Laboratory

Laboratory sessions take part in person in the lab rooms assigned according to the schedule.
Student groups are divided in half (into two equally-sized subgroups or with a maximum difference of one student).
**The maximum number of students in a lab slot is 16.**
Starting from the third week, the attendance list for the laboratory becomes fixed.

Transfers between subgroups are only allowed in objective situations.
Reasons such as "I'm employed," "I have classes for another course," or "the schedule suits me better" are not considered.
If you have an objective situation, you can request a transfer between subgroups by sending an email to [Răzvan Deaconescu](mailto:razvan.deaconescu@upb.ro) with the subject `[SO][Transfer Request] NAME Surname - Group`, in which you describe the situation.
You will be informed if the transfer is accepted.

### Pins

After the semester, students will be rewarded with distinctions based on their involvement in certain activities.

The distinctions to be awarded in the 2023-2024 academic year are as follows:

- 8 distinctions for involvement in lecture activities.
- 20 distinctions for involvement in laboratory activities.
- 5 distinctions for interesting implementations of assignments.
- 8 distinctions for exam results.
- 10 distinctions for community involvement (pull requests, forum discussions, etc.).

### Retaking the Final Exam

During the autumn exam and the special summer session (**only for 4th year students**), only the exam can be retaken.
Assignments cannot be resubmitted.

You can retake the exam to improve the grade obtained in the first exam session.
In the case of participation for grade improvement, the grade obtained in this manner will replace the grade in the first exam session.

Students in the 4th year can also take the exams in the resit/improvement session in the autumn and the special summer session.
4th year students can participate in both the summer and autumn sessions.

You can participate in only one exam during a session.
Once the exam dates are agreed upon (generally, there are two exam dates in the resit/improvement session), we will open discussion threads for registration for one of the two dates.
Then we will plan and announce the details.
If, after the resit/improvement session in the fall, you still do not obtain a passing score, you will need to retake the course in the next academic year.

### Retaking the Course

By default, the grades for the previous academic year (2022-2023) are reset on October 1, 2023.
If you did not graduate from the course in the 2022-2023 academic year, you will need to retake it in the current academic year (2023-2024), with the possibility of retaining some components, as detailed below:

- If you wish, you can retain the grades for the course's practical components (laboratory and/or assignments).
  You **cannot** retain the grades for lecture components (lecture tests and exam).
- Students interested in preserving their grades should respond on [the designated Moodle thread](https://curs.upb.ro/2023/mod/forum/discuss.php?d=96) by **Tuesday, October 31, 2023, 23:00**.
- The rules and grading system for students retaking the course are the same as for students in the current year (lecture tests + exam, assignments, etc.).
- Students retaking the course can participate in any lab session as long as there are available slots.
  Like other students, the attendance list becomes fixed starting from the third week.
- Students retaking the course can participate in any lecture, lecture test, and exam, regardless of the series to which they belonged.

By default, the grades for the 2023-2024 academic year will be reset on October 1, 2024.
If you do not graduate from the course in the 2023-2024 academic year, you will need to retake it in the 2024-2025 academic year, with the possibility of retaining some components, as detailed above.
