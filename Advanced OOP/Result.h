#ifndef HEADER_RESULT
#define HEADER_RESULT

#define NOT_FOUND_ACTOR "There is no a such actor!\n"
#define NOT_FOUND_SUBJECT "There is no a such subject!\n"
#define ADMNISTRATION_REMOVE "I'm the ADMIN!!!Can not remove me or my posts!!:)\n"
#define ADMINISTRATION_BLOCK "I'm the ADMIN!!!Can not block me!!:)\n"
#define NO_PERMISSION_REMOVE_USER "The actor has no permission to remove other users!\n"
#define NO_PERMISSION_REMOVE_POST "The actor has no permission to remove other posts!\n"
#define NO_PERMISSION_ADD_USER "The actor has no permission to add other users!\n"
#define NO_PERMISSION_BLOCK_UNBLOCK "The actor has no permission to block/unblock other users!\n"
#define BLOCKED_USER "The actor is BLOCK and can only view other posts!\n"
#define SUCCSSES_REMOVE_USER "User was successfully removed!\n"
#define SUCCSSES_REMOVE_OWN_POST "The own posts was removed!\n"
#define SUCCSSES_REMOVE_OTHER_POST "The posts of sbj is removed!\n";
#define SUCCSSES_ADD_USER "User was successfully added!\n"
#define SUCCSSES_RENAME "The new name is SET!\n"
#define SUCCSSES_BLOCK_UNBLOCK "Actor  successfully block/unlock the sbj!\n"
#define SUCCSSES_HTML "HTML FOR POST IS CREATED!\n"
#define SUCCSSES_HTML_ALL "HTML FILE FOR ALL POST OF SUBJECT IS CREATED!\n"
#define ALREADY_EXIST "The user with this name already exist!\n"
#define INVALID_POST "The posts not exist or is already removed!\n"
#define INVALID_ARGUMENT_PASS "NULL PTR PASS TO FUNCTION!\n"
#define FILE_PROBLE "Problem wile operating the file!\n"
#define NO_POUST_USERS "The user still not have any posts!\n"
#define INCORRECT_AGE "The age must be in range(18-99)!\n"

enum Result
{
	NO_POST=-4,
	PROBLEN_FILE ,
	NOSUCH_POST,
	NOSUCH_USER,
	REMOVE_ADMIN,
	NO_PERMISSION,
	SUCCSESS,
	USER_BLOCKED,
	INVALID_ARGUMENT,
	UNKNOWN_POST
};
#endif
