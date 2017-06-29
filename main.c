#include "ft_printf.h"

/*
You have to recode the libc’s printf function.
• Your function will be called ft_printf and will be prototyped similarly to printf.
• You won’t do the buffer management in the printf function.

%[флаги][ширина][точность][модификаторы][тип преобразования]

• You must manage the flags 

#		Использовать альтернативную форму представления выводимого числа.
        При выводе чисел в шестнадцатеричном формате (преобразователь 'х' или 'Х') перед числом будет указываться 0х или 0Х соответственно.
        При выводе чисел в восьмеричном формате (преобразователь 'о')перед числом будет указываться 0. При выводе чисел с плавующей точкой (преобразователи e, E, f, g и G)
        всегда будет содержаться десятичная точка (по умолчанию десятичная точка выводится только при ненулевой дробной части).
        При использовании преобразователей g и G хвостовые нули не будут удаляться (по умолчанию удаляются).
0		Если не указан флаг '-', то слева от выводимого числа будут выведены символы '0' для подгона числа к указанной ширене. 
        Если для преобразователей d, i, o, x или X указана точность, то флаг 0 игнорируется.
- 		Результат преобразования выравнивается по левому краю (по умолчанию - по правому краю)
+ 		Перед положительными числами выводится знак '+', а перед отрицательыыми - знак '-' (по умолчанию выводится только знак '-' перед отрицательыми числами)
space 	Если не указан модификатор '+', то перед положительными числами, на месте знака числа, будет выводиться пробел.

• You must manage the (flags)modificators 
hh		Для вывода числа типа char или unsigned char. Или для явного преобразования при выводе целочисленного числа к типу char или unsigned char. 
        Используется с :d, i, o, u, x и X, n.

h		Для вывода числа типа short int или unsigned short int. Или для явного преобразования при выводе целочисленного числа к типу short int или unsigned short int. 
        Используется с :d, i, o, u, x и X, n.

l		Для вывода числа типа long int или unsigned long int. Или для явного преобразования при выводе целочисленного числа к типу long int или unsigned long int.
        Используется с :d, i, o, u, x и X, n.
ll		Для вывода числа типа long long int или unsigned long long int. Или для явного преобразования при выводе целочисленного числа к типу long long int или unsigned long long int.
        Используется с :d, i, o, u, x и X, n.

j				
z		
        •An optional length modifier, that specifies the size of the argument.  The following length modi-
         fiers are valid for the d, i, n, o, u, x, or X conversion:

         Modifier          d, i           o, u, x, X            
         hh                signed char    unsigned char         
         h                 short          unsigned short        
         l (ell)           long           unsigned long         
         ll (ell ell)      long long      unsigned long long    
         j                 intmax_t       uintmax_t             
         z                 (see note)     size_t                
         
         Note: the z modifier, when applied to a d or i conversion, indicates that the argument is of 
         a signed type equivalent in size to a size_t.

        •The following length modifier is valid for the c or s conversion:

         Modifier    c         s
         l (ell)     wint_t    wchar_t *

         If the l (ell) modifier is used, the wint_t argument shall be converted to a wchar_t, and the
             (potentially multi-byte) sequence representing the single wide character is written, including
             any shift sequences.  If a shift sequence is used, the shift state is also restored to the
             original state after the character.

• You must manage the minimum field-width
	Спецификатор [ширина] задаёт минимальный размер выводимого числа в символах.
    Если количество символов в выводимом числе меньше указанной минимальной ширины, то недостоющее количество символов заполняется 
    нулями или пробелами слева или справа в зависимости от указанных флагов. Ширина указывается либо целым числом, либо символом * с последующим
    указанием имени переменной типа int, содержащей значение ширины, перед аргументом к которому он относится.
    Если аргумент имеет отрицательное значение, то он эквивалентен соответствующему положительному значению с флагом "-".
• You must manage the precision
	Действия спецификатора [точность] зависит от типа выводимого числа: 
	- Для типов d, i, o, u, x, X определяет минимальное число выводимых цифр.
    Если количество выводимых цифр в числе меньше, чем указано в спецификаторе [точность], то выводимое число будет дополнено нулями слева.
    Например, если при выводе числа 126 указать точность 4, то на экран будет выведено число 0126 
• You have to manage the following conversions: 

d,i Вывод целого числа со знаком в десятичной систем счисления. По умолчанию выводится число размером sizeof( int ),
    с правым выравниванием, указанием знака только для отрицательных чисел.
o	Вывод целого числа без знака в восьмеричной систем счисления. По умолчанию выводится число размером sizeof( int ), с правым выравниванием.
u	Вывод целого числа без знака в десятичной систем счисления. По умолчанию выводится число размером sizeof( int ), с правым выравниванием.
x,X	Вывод целого числа без знака в шестнадцетеричной систем счисления. Причем для преобразования x используются символы abcdef, а для X - символы ABCDEF.
    По умолчанию выводится число размером sizeof( int ), с правым выравниванием.
s	Вывод строки, на которую ссылается указатель в аргументе функции printf. Строка выводится пока не будет встречен символ конец строки (/0).
    По умолчанию строка должна обозначаться как char*. Если указан модификатор l, то строка интерпитируется как wchar_t*.
S	(Unicode).Аналогичен преобразованию s с модификатором l. 
C	(Unicode).(? Аналогичен преобразованию c с модификатором l. ?)
		https://forum.intra.42.fr/topics/15759/messages/last
p	Вывоqд указателя. Результат ввода зависит от архитектуры и используемого компилятрора. (as if by `%#x' or `%#lx')
c	Вывод символа, соответстветсвующего числу указанному в аргументе функции. По умолчанию число приводится к типу unsigned char.
D,O,U	The long int argument is converted to signed decimal, unsigned octal, or unsigned decimal, as if the format had been ld, lo, lu respectively.
    These conversion characters are deprecated, will eventually disappear.

Правда компилятор выдает предупреждение(пытаемся всунуть обычный int в long) на первый printf при:
printf("Positive %ld\n", 42);
printf("Positive %D\n", 42);
Хотя если подставить L после аргумента, предупреждение исчезает:
printf("Positive %ld\n", 42L);
Это к тому, что D принимает без предупреждений обычный int в качестве long а ld - ругается.

• You must manage %%. A `%' is written.  No argument is converted.  The complete conversion specification is `%%'.

In no case does a non-existent or small field width cause truncation of a numeric field; if the result
     of a conversion is wider than the field width, the field is expanded to contain the conversion result.

*/

int		main(int argc, char **argv)
{
	if (argc == 2)
	{
		ft_printf(argv[1]);
	}
	else
	{
		//here must be hard-tests
        // ft_printf("");
        ft_printf("test_char=%c", 'x');
	}
	return (0);
}
