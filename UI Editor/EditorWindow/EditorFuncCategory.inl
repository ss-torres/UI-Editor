#ifndef EDITOR_FUNC_CATEGORY_INL
#define EDITOR_FUNC_CATEGORY_INL

/*
 * 文件名：EditorFuncCategory.inl
 * 作用：创建一系列与EditorFunc有关的类，形式上这些类型为EditorFunc的派生类
 * 说明：这些类只是形式上的作用，真正的对EditorFunc的虚函数的重构出现在SimpleWindow中
 * 对以下类型的特例化中，所以以下类型的实现，甚至派生都没有实际的作用，不过，在SimpleWindow
 * 的特例化中，会根据以下的类的继承结构
 */

namespace inner
{
	// 用在SimpleWindow的特例化中
	class EditorEditableFunc : public EditorFunc
	{
	public:
		using FuncBaseType = EditorFunc;
	public:
		using EditorFunc::EditorFunc;
		~EditorEditableFunc() override = default;
	};

	// 用在ContainerWindow的特例化中
	class EditorContainerFunc : public EditorEditableFunc
	{
	public:
		using FuncBaseType = EditorFunc;
	public:
		using EditorEditableFunc::EditorEditableFunc;
		~EditorContainerFunc() override = default;

	};
}

#endif	// EDITOR_FUNC_CATEGORY_INL
