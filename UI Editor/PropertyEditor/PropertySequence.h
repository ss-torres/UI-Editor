#ifndef PROPERTY_SEQUENCE_H
#define PROPERTY_SEQUENCE_H

/*
 * 文件名：AbstractPropertySequence
 * 作用：属性编辑器中显示属性的顺序
 * 做法：同一类型的窗口类，存在同一种属性排列顺序，即固定的属性，固定的属性排列，可以考虑，
 * 当第一次获取的时候，根据配置文件中获得的信息进行排序，之后获取，直接返回值
 */

#include "AbstractPropertySequence.h"
#include <typeinfo>

class PropertySequence : public AbstractPropertySequence
{
public:
	PropertySequence() : AbstractPropertySequence() {}
	~PropertySequence() override {}

protected:
	void sortPropertySequence() override {}

private:

};

#endif	// PROPERTY_SEQUENCE_H
