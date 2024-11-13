import sys
from os import path
from os.path import join
from os import walk
import argparse

copyright_header = \
"Intel Proprietary\n\
\n\
Copyright 2021 Intel Corporation All Rights Reserved.\n\
\n\
Your use of this software is governed by the TDX Source Code LIMITED USE LICENSE.\n\
\n\
The Materials are provided “as is,” without any express or implied warranty of any kind including warranties\n\
of merchantability, non-infringement, title, or fitness for a particular purpose.\n\"


def list_files_exclude_path(root, files_list, exclude_path=None):
    """
    list_files_exclude_path
    :param root: the current path to (recursively) find all files under
    :param files_list: Output param that will populate the list of files found under the current root dir
    :param exclude_path: Currently not in use !!!
    """
    for path, subdirs, files in walk(root):
        if exclude_path and path.find(exclude_path) >= 0:
            continue
        for file in files:
            #print('{}  /  {}'.format(path, file))
            files_list.append(join(path, file))
    return files_list


def check_if_copyrigh_exists(lines, header):
    """
    check_if_copyrigh_exists
    Checks the lines for the copyright notice
    :param lines: list of lines from the file in which to check for the copyright notice
    :param header: a string containing the copyright notice
    """
    found = False
    for h_l in header.splitlines():
        for l in lines:
            if l.find(h_l) >= 0:
                found = True
                break
        if not found:
            return False
        found = False

    return True


def add_copyrigh_header_to_file(file_name, header, update_mode):
    """
    add_copyrigh_header_to_file
    Check if the given file_name contains the copyright notice, and updates if depending on update_mode
    :param file_name: the name of the file
    :param header: a string containing the copyright notice
    :param update_mode: mode of check and update. One of ['Check Only' / 'Update Interactive' / 'Update Force']
    """
    f = open(file_name, mode='r', encoding='utf-8')
    comment_prefix = ''
    filename_no_ext, file_ext = path.splitext(file_name)
    if file_ext == '.c' or file_ext == '.h' or file_ext == '.cpp':
        comment_prefix = '// '
    elif file_ext == '.S':
        comment_prefix = '// '
    elif file_ext == '.mk' or file_name == 'Makefile':
        comment_prefix = '# '

    lines = f.readlines()
    f.close()
    
    copyright_exists = check_if_copyrigh_exists(lines[0:20], header)
    if copyright_exists:
        #print('copyright notice exists in file {}.'.format(file_name))
        return True
    if update_mode == 'Check Only':
        print('"{}" does not contain the copyright notice'.format(file_name))
        return False
    if update_mode == 'Update Interactive':
        print('{} does not contain the copyright notice'.format(file_name))
        answer = input('Do you want to update it [YN] ? ')
        answer = answer.lower()
        if answer != 'y' and answer != 'yes':
            print('you chose not to update the file...')
            return True

    f = open(file_name, mode='w', encoding='utf-8')
    for h in header.splitlines():
        #print(comment_prefix + ' ' + h)
        f.write(comment_prefix + h + '\n')
    f.writelines(lines)
    f.close()
    return True


def add_copyright_header(files_list, header, update_mode):
    """
    add_copyright_header
    Loops over all the files in 'file_list' and update them all
    :param files_list: a list of the files to update
    :param header: a string containing the copyright notice
    :param update_mode: mode of check and update. One of ['Check Only' / 'Update Interactive' / 'Update Force']
    """
    has_bad_files = False
    for f in files_list:
        passed = add_copyrigh_header_to_file(f, header, update_mode=update_mode)
        if not passed:
            has_bad_files = True

    return has_bad_files


def parse_args():
    """
    parse_args
    Parses the command line arguments
    """
    parser = argparse.ArgumentParser(description='Copyright script')
    parser.add_argument('-r', required=False, action='store', dest='root', help='Root folder', default='../')
    parser.add_argument('-i', required=False, action='store', dest='include_paths', type=str, nargs='*', default=[], help='A list of relative paths to include. These paths are appended to the root path')
    parser.add_argument('-x', required=False, action='store', dest='exclude_paths', type=str, nargs='*', default=[], help='!! CURRENTLY NOT IN USE!!. A list of relative paths to exclude.')
    parser.add_argument('-m', required=False, action='store', dest='update_mode', default='Check Only', choices=['Check Only', 'Update Interactive', 'Update Force'], help='How to check or update copytigh notice')
    return parser.parse_args()


if __name__ == '__main__':
    files_list = []

    args = parse_args()
    root_dir = args.root
    include_dirs = args.include_paths
    exclude_dirs = args.exclude_paths

    exclude_dirs = []

    if isinstance(include_dirs, list):
        for include_dir in include_dirs:
            files_list = list_files_exclude_path(join(root_dir, include_dir), files_list=files_list, exclude_path=exclude_dirs)
    else:
        files_list = list_files_exclude_path(join(root_dir, include_dirs), files_list=files_list, exclude_path=exclude_dirs)
    #print(files_list)

    has_bad_files = add_copyright_header(files_list, copyright_header, args.update_mode)
    if has_bad_files:
        print('\nThere are files that don\'t contain the copyright notice\n')
        sys.exit(1)
