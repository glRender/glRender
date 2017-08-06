#!/usr/bin/env python
# -*- coding: UTF-8 -*-
import sys
import argparse
import subprocess
import os.path
import os
import time
import platform
import shlex

version = "0.0.1"

def path_creatable(pathname):
	'''
	if the current user has sufficient permissions to create the passed
	pathname; Exception otherwise.
	'''
	# Parent directory of the passed path. If empty, we substitute the current
	# working directory (CWD) instead.
	dirname = os.path.dirname(pathname) or os.getcwd()
	if not(os.access(dirname, os.W_OK)):
		msg = "%r <- bad file name " % pathname
		raise argparse.ArgumentTypeError(msg)
	return pathname

def path_to_dir(path):
	if not(bool(os.path.isdir(path))):
		msg = "%r no such dir " % path
		raise argparse.ArgumentTypeError(msg)
	return path


def createParser ():
	# Создаем класс парсера
	parser = argparse.ArgumentParser(
			prog = 'buildInfoCreator',
			description = '''''',
			epilog = '''Lizin Aleksandr (sogimu), Email: sogimu@nxt.ru, 2017''',
			add_help = True
			)
 
	parser.add_argument ("-f", "--file-name-to-fill", type=path_creatable, default="buildInfo.hpp", required=False, help = 'Path to file will be generated. That file will have struct for C++11 with build information. Default: ./buildInfo.hpp')
	parser.add_argument ("-d", "--path-to-repo", type=path_to_dir, default=".", required=False, help = 'Path to dir with git repository: Default .')
	parser.add_argument ("-b", "--build-id",     type=str, required=False, help = 'Build ID')
	parser.add_argument ("-o", "--os",           type=str, required=False, help = 'OS info')
	parser.add_argument ("-c", "--compiler",     type=str, required=False, help = 'Compiler info')
	parser.add_argument ("-n", "--dry-run", action='store_true', required=False, help = 'Dry run')
	parser.add_argument ("-v", "--version", action='version', version='%(prog)s {}'.format (version), help = 'Version of %(prog)s')

	return parser

class bcolors:
	HEADER = '\033[95m'
	OKBLUE = '\033[94m'
	OKGREEN = '\033[92m'
	WARNING = '\033[93m'
	FAIL = '\033[91m'
	ENDC = '\033[0m'
	BOLD = '\033[1m'
	UNDERLINE = '\033[4m'

class cd:
	"""Context manager for changing the current working directory"""
	def __init__(self, newPath):
		# sys.stdout.write("\n" + bcolors.BOLD + "> cd " + newPath + bcolors.ENDC + "\n")
		# sys.stdout.flush()
		self.newPath = os.path.expanduser(newPath)

	def __enter__(self):
		self.savedPath = os.getcwd()
		try:
			os.chdir(self.newPath)
		except OSError:
			raise Exception(bcolors.FAIL + "Path: {0}. Path to dir not found!".format(self.newPath) + bcolors.ENDC)

	def __exit__(self, etype, value, traceback):
		os.chdir(self.savedPath)

def run(cmd):
	sys.stdout.write("\n" + bcolors.BOLD + "> " + cmd + bcolors.ENDC + "\n")
	sys.stdout.flush()
	output = subprocess.check_output(shlex.split(cmd))
	sys.stdout.write("\n")
	sys.stdout.flush()
	return output

def concat(array, prefix):
	result = ""
	for element in array:
		if len(result) > 0:
			result += prefix + element
		else:
			result += element
	return result

def formatIfEmpty(data, replacementIfEmpty):
	result = data
	if len(data) == 0 or data == '\n':
		result = replacementIfEmpty
	return result

def getFileText(filePath):
	content = ""
	with open(filePath, "a+") as f:
		for line in f:
			content += line
	f.close()
	return content

def writeToFile(data, file):
	f = open(file, "w")
	f.write(data)
	f.close()

def trimSpacesInArray(array):
	result = []
	for elem in array:
		if elem != "":
			result.append(elem)
	return result

def getCurrentCommitInfo():
	branch = "";
	shortHash = "-"
	try:
		output = run("git branch -v".format())
		lines = output.split('\n')
		for line in lines:
			words = trimSpacesInArray(line.split(' '))
			if words[0] != '*':
				continue
			branch = words[1]
			shortHash = words[2]
			return {"shortHash": shortHash, "branch": branch}
	except:
		return {"shortHash": shortHash, "branch": branch}

def getCurrentCommitStatus():
	changedFiles = [];
	untrackedFiles = []
	try:
		output = run("git status --porcelain".format())

		lines = output.split('\n')
		for line in lines:
			words = line.split(' ')
			if words[1] == 'M':
				changedFiles.append(words[2])
			elif words[0] == '??':
				untrackedFiles.append(words[1])
		return {"changedFiles": changedFiles, "untrackedFiles": untrackedFiles}
	except:
		return {"changedFiles": changedFiles, "untrackedFiles": untrackedFiles}

def getCurrentCommitTag():
	tag = "";
	try:
		output = run("git tag -l --points-at HEAD".format())        

		if len(output) > 0:
			tag = output
		return tag
	except:
		return tag

class PlatformInfo:
	def osName(self):
		return platform.system()
	def distName(self):
		distName = "None_None"
		if self.osName() == "Linux":
			distName = platform.dist()[0]+'_'+platform.dist()[1]
		elif self.osName() == "Windows":
			distName = platform.win32_ver()[0]+'_'+platform.win32_ver()[1]
		return distName

	def fullPlatformName(self):
		return self.osName() + '_' + self.distName()

template = """#pragma once
/*
Do not try edit this file! Any changes will be lost!
*/

#include <vector>
#include <string>
#include <cstring>

struct BuildInfo
{
	BuildInfo()
	{
		shortHash = "%s";
		branch = "%s";
		tag = "%s";
		buildId = "%s"; 
		os = "%s"; 
		compiler = "%s"; 
		dateTime = "%s"; 
		changedFiles = std::vector<const char *>({"%s"});
		untrackedFiles = std::vector<const char *>({"%s"});
	}
	const char * shortHash;
	const char * branch;
	const char * tag;
	const char * buildId;
	const char * os;
	const char * compiler;
	const char * dateTime;
	std::vector<const char *> changedFiles;
	std::vector<const char *> untrackedFiles;

	std::string info()
	{
		std::string versionInfo = "";
		versionInfo += withRightPad(u8"Short hash:", 24, ' ') + shortHash + '\\n';
		versionInfo += withRightPad(u8"Branch:", 24, ' ')        + branch + '\\n';
		versionInfo += withRightPad(u8"Tag:", 24, ' ')        + tag + '\\n';
		versionInfo += withRightPad(u8"Build ID:", 24, ' ') + buildId + '\\n';
		versionInfo += withRightPad(u8"OS:", 24, ' ') + os + '\\n';
		versionInfo += withRightPad(u8"Compiler:", 24, ' ') + compiler + '\\n';
		versionInfo += withRightPad(u8"Date and time:", 24, ' ') + dateTime + '\\n';

		writeList(versionInfo, u8"Changed files:", changedFiles);
		writeList(versionInfo, u8"Untracked files:", untrackedFiles);
		return versionInfo;
	}

private:
	std::string withRightPad(std::string keyName, uint width, char c) const
	{
		uint keyNameLength = strlen_utf8(keyName);
		int additionSize = (int)width-(int)keyNameLength;

		std::string result = keyName;

		if (additionSize > 0)
		{
			for (int i=0; i < additionSize; i++)
			{
				result += c;
			}
		}
		return result;
	};

	void writeList(std::string & target, std::string preamble, std::vector<const char *> & list) const
	{
		bool isFirstLine = true;
		for(const char * file : list)
		{
			if (isFirstLine)
			{
				if (file == std::string(""))
				{
					target += withRightPad(preamble, 24, ' ') + "-\\n";
				}
				else
				{
					target += withRightPad(preamble, 24, ' ') + file + "\\n";

				}
				isFirstLine = false;
			}
			else
			{
				target += withRightPad(" ", 24, ' ') + file + "\\n";
			}
		}
	};

	std::size_t strlen_utf8(const std::string & str) const
	{
		std::size_t length = 0;
		for (char c : str) {
			if ((c & 0xC0) != 0x80) {
				++length;
			}
		}
		return length;
	}
};"""

if __name__ == '__main__':
	print(sys.argv[0:])
	parser = createParser()
	namespace = parser.parse_args(sys.argv[1:])

	abcPathToRepo = os.path.abspath(namespace.path_to_repo)

	print("Path to git-repo: {}".format(abcPathToRepo))
	with cd(abcPathToRepo):
		commitInfo = getCurrentCommitInfo()
		commitStatus = getCurrentCommitStatus()
		commitTag = getCurrentCommitTag()
		buildId = namespace.build_id if namespace.build_id != None else ""
		osInfo = namespace.os if namespace.os != None else PlatformInfo().fullPlatformName()
		compiler = namespace.compiler if namespace.compiler != None else ""
		dateTime = time.strftime("%d/%m/%Y %I:%M:%S")

		result = template % (
			formatIfEmpty(commitInfo["shortHash"], "-"), 
			formatIfEmpty(commitInfo["branch"], "-"), 
			formatIfEmpty(commitTag, "-"),
			formatIfEmpty(buildId, "-"),
			formatIfEmpty(osInfo, "-"),
			formatIfEmpty(compiler, "-"),
			formatIfEmpty(dateTime, "-"),
			concat(commitStatus["changedFiles"], "\", \""),
			concat(commitStatus["untrackedFiles"], "\", \"")
		)

		fullPathToFile = os.path.join(namespace.path_to_repo, namespace.file_name_to_fill)

		if namespace.dry_run == True:
			sys.stdout.write("\n" + bcolors.HEADER + "The file %s will be updated with following text after normal run:" % (os.path.abspath(fullPathToFile)) + bcolors.ENDC)
			sys.stdout.write("\n" + bcolors.BOLD + "%s\n" % (result) + bcolors.ENDC)
			sys.stdout.flush()
		elif result != getFileText(fullPathToFile):
			writeToFile(result, fullPathToFile)
			sys.stdout.write("\n" + bcolors.BOLD + "%s\n" % (result) + bcolors.ENDC)
			sys.stdout.write("\n" + bcolors.OKGREEN + "The file %s updated.\n" % os.path.abspath(fullPathToFile) + bcolors.ENDC)
			sys.stdout.flush()
		else:
			sys.stdout.write("\n" + bcolors.OKGREEN + "The file %s actual. No changes.\n" % os.path.abspath(fullPathToFile) + bcolors.ENDC)
			sys.stdout.flush()


