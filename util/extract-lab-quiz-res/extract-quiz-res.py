import sys
import csv
import argparse
import json

def main():
    desc = """
    Extracts lab quiz results from a csv file exported from Moodle.
    It expects an input file with the usernames of each student on a separate line.
    The results are written in an output csv file provided by the user.
    """
    parser = argparse.ArgumentParser(description=desc)
    parser.add_argument('-i', '--input_quiz_res', type=str, required=True,
                        help="path to csv file with Moodle quiz results")
    parser.add_argument('-s', '--input_stud_users', type=str, required=True,
                        help="path to file with student usernames, one per line")
    parser.add_argument('-o', '--output_quiz_res', type=str, default='extracted-res.csv',
                        help="path to log file")
    args = parser.parse_args()

    all_students = get_students_from_csv(args.input_quiz_res)
    target_students = get_target_students(args.input_stud_users)

    did_init_csv = False
    with open(args.output_quiz_res, 'w') as res_file:
        for target in target_students:
            if target not in all_students:
                print(f"{target} did not submit quiz")
                continue

            target_stud_res = all_students[target]
            if not did_init_csv:
                csv_writer = csv.DictWriter(res_file, target_stud_res.keys())
                csv_writer.writeheader()
                did_init_csv = True
            csv_writer.writerow(target_stud_res)

def get_students_from_csv(csv_file):
    students = []
    with open(csv_file, 'r') as f:
        r = csv.reader(f)
        header = None
        for row in r:
            if header is None:
                header = row
            else:
                d = {}
                for idx in range(len(header)):
                    d[header[idx]] = row[idx]
                students.append(d)

    students_dict = {}
    for student in students:
        username = student["Email address"].split("@")[0]
        student["Username"] = username
        if len(username):
            students_dict[username] = student

    # print(json.dumps(students_dict, indent=4))
    return students_dict

def get_target_students(students_list_file):
    students = []

    with open(students_list_file, 'r') as f:
        for line in f:
            students.append(line.strip());

    # print(students)
    return students

if __name__ == "__main__":
    main()

