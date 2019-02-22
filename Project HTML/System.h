#ifndef SYS_HEADER_INCLUDED
#define SYS_HEADER_INCLUDED
#include"TagFactory.h"
class System
{
public:
	System(const char*fileName);
	System(const System&other);
	System& operator=(const System&other);
	~System();

public:
	void addTags(const char*command,const char*des,const char*content, const char*linkDes = 0, unsigned short n = 0);
	void removeTag(size_t index);
	void moveTo(size_t index, size_t where);
	void addAtt(size_t tag_index, const char*name, const char*value);
	bool saveData()const;
public:
	const char*getDes(size_t index)const;
	const char*getType(size_t index)const;
	size_t getSize()const { return size; }

private:
	void setFileName(const char*fileName);
	void setSize(size_t size);
	void setCap(size_t cap);
	void setTags(size_t size);
private:
	void copyFrom(const System&other);
	void clean(Tag**&tags,size_t size);
	void resize(size_t newCap);
	void allToNull(size_t size);
private:
	const char*filename;
	Tag**tags;
	size_t size;
	size_t cap;
};
#endif
