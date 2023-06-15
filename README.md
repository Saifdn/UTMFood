# UTMFood
Project Programming Technique II

UTM Food is a console application that allows users to order food from various vendors in and 
around the University Technology Malaysia (UTM) campus. The platform is inspired by Grab 
Food and aims to provide a convenient and seamless experience for users to order and pay for 
food from their favorite vendors. This project proposal outlines the problem background, 
proposed solution, objectives, and scope of the project.


15 june 2023/thursday(5.00pm):
I have done vendor display, vendor selection and menuitem display in test2.cpp in order to no lose the older version.
During the process of coding i faced some errors i'm clueless about, where it says:
1. use of deleted function 'std::basic_fstream<_CharT, _Traits>::basic_fstream(const std::basic_fstream<_CharT, _Traits>&) [with _CharT = char; _Traits = std::char_traits<char>]' Ln185 in test2.cpp
2. use of deleted function 'MenuItem::MenuItem(const MenuItem&)' Ln446 in test2.cpp

15 june 2023/thursday(11.00pm):
1. the error have successfully been fixed by using passing via pointer of menuitem
2. the program now are able to ask multiple order from customer and display all the food ordered and the price of each of the food ordered. Lastly display total payment.
