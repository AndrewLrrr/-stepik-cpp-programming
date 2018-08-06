struct A
{
    int field1;
    mutable int field2;
};

int main() {
    int const i = 1;
    int * p = 0;
    // p = &i;  не скомпилируется,  т.к. это преобразование int const * -> int *

    // В этой строке происходит запрещённое преобразование int ** -> int const **
    int ** pp = &p;  // теперь *pp указывает на переменную p

    // следующая строка скомпилируется, т.к. *pp имеет тип int const*
    *pp = &i; // это соответствует p = &i
    *p = 2; // изменяем значение переменной i


    const A obj;
    obj.field1 = 0; // Ошибка
    obj.field2 = 0; // ОК
}