Sql语句判定器。

可以通过此学习 模板类、缺省参数、typeid 等等。以及mysql，sqlite 的内部中的一些游标、等等原理和机制。

通过模板类和缺省参数来获得不同长度以及不同类别的输入。
	template<typename T>
	template <typename ...Args>
通过 typeid 把不同的输入类型转换成 str。