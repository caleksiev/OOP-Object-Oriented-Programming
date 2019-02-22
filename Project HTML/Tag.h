#ifndef TAG_HEADER_INCLUDED
#define TAG_HEADER_INCLUDED
#include"Attribute.h"
class Tag
{
public:
	Tag(const char*des,const char*cont);
	Tag(const Tag&other);
	Tag& operator=(const Tag&other);
	virtual ~Tag();

public:
	virtual const char*whatAmI()const = 0;
	virtual Tag*clone()const = 0;
	bool virtual writeOnHile(std::ostream&os)const=0;
	void addAtr(const char*name, const char*value);
public:
	const char*getDes()const { return description; }
private:
	void setDescription(const char*des);
	void setContent(const char*cont);
	void setAttribute(size_t size);
	void setSize(size_t size);
	void setCap(size_t cap);
private:
	void clean(char*&description, char*&content, Attribute**&attribute,size_t cap);
	void cleanAtt(Attribute**&attribute,size_t size);
	void copyFrom(const Tag&other);
	void resize(size_t newCap);
private:
	void allToNull(size_t cap);

	
protected:
	char*description;
	char*content;
	Attribute**attribute;
	size_t size;
	size_t cap;
};
#endif
