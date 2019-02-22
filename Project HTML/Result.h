#ifndef RESULT_HEADER_INCLUDED
#define RESULT_HEADER_INCLUDED

#define TAG_ADDED "The tag was successfully added!\n"
#define ATTR_ADDED "The attribute was successfully added!\n"
#define FILE_SAVED "The file was successfully saved!\n"
#define FILE_NOT_SAVED "Problem while operating with the file!\n"
#define TAG_MOVED "The tag was successfully moved!\n"
#define TAG_NOT_FOUND "There is no a tag with that description!\n"
#define TAG_REMOVED "The tag was successfully removed!\n"
enum Result
{
	WRONG_FILE_PATH=0,
	FILE_MUST_BE_HTML,
	NEW_FILE_CREATED,
	FILE_EXIST,
	FILE_NOT_OPEN,
	FILE_PROBLEM_READ,
	UKNOWN_FILE_DATA,
	NO_DESCR_IN_FILE,
	SUCCSEES_FILE_READ,
	END_OF_FILE,
	NO_PROBLEM_FILE,
	WHAT_IS_THIS,
};
#endif
