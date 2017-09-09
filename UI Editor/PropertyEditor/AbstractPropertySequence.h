#ifndef ABSTRACT_PROPERTY_SEQUENCE_H
#define ABSTRACT_PROPERTY_SEQUENCE_H

/*
 * 文件名：AbstractPropertySequence
 * 作用：属性编辑器中显示属性的顺序
 */

class AbstractPropertySequence
{
public:
	AbstractPropertySequence() {}
	virtual ~AbstractPropertySequence() {}

protected:
	virtual void sortPropertySequence();

};

#endif	// ABSTRACT_PROPERTY_SEQUENCE_H
