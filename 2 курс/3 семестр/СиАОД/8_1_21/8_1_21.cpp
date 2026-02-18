#include "ShannonFano.h"
#include <windows.h>

int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	ShannonCompressor worker;

	// std::string my_text =
	// 	"Зуба зуба, зуба зуба, Зуба дони дони мэ, "
	// 	"А шарли буба раз два три, А ми раз два три замри.";

	std::string my_text = "Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat. Ut wisi enim ad minim veniam, quis nostrud exerci tation ullamcorper suscipit lobortis nisl ut aliquip ex ea commodo consequat. Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi.";

	// std::string my_text =
 //        "Алгоритм Шеннона-Фано — один из первых алгоритмов сжатия, разработанный независимо Клодом Шенноном "
 //        "и Робертом Фано в 1949 году. Этот алгоритм использует коды переменной длины, основанные на вероятности "
 //        "появления символов в исходном тексте. Чем чаще встречается символ, тем короче его код. "
 //        "Shannon-Fano coding is an entropy encoding technique for lossless data compression. "
 //        "It was one of the first compression algorithms to use variable-length codes. "
 //        "Повторяющиеся слова и фразы: сжатие данных, сжатие данных, кодирование информации, "
 //        "энтропийное кодирование, алгоритмы сжатия без потерь. "
 //        "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt "
 //        "ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco "
 //        "laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in "
 //        "voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat "
 //        "non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. "
 //        "Еще больше текста на русском языке для проверки работы с кириллицей: "
 //        "Сжатие информации — процесс уменьшения объема данных при сохранении содержащейся в них информации. "
 //        "Методы сжатия делятся на два основных класса: с потерями и без потерь. "
 //        "Алгоритмы без потерь позволяют точно восстановить исходные данные, в то время как "
 //        "алгоритмы с потерями допускают некоторые искажения. "
 //        "1234567890 !@#$%^&*() ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz "
 //        "Повторения: ааааа бббб ввв ггг дд еее жж зз иии йй кк лл мм нн ооо пп рр сс тт уу фф хх цц чч шш щщ ьыъ эюя"
 //        "\n\nМногострочный текст:\n"
 //        "Строка 1: Первая строка для тестирования.\n"
 //        "Строка 2: Вторая строка с другими символами.\n"
 //        "Строка 3: Третья строка содержит цифры 123 и знаки !?.\n"
 //        "Строка 4: Четвертая строка для завершения теста.\n\n"
 //        "Заключительная часть: Алгоритм Шеннона-Фано не всегда дает оптимальное сжатие, "
 //        "но он важен с исторической точки зрения и является предшественником более эффективного "
 //        "алгоритма Хаффмана, разработанного три года спустя.";


	std::ofstream f("task.txt", std::ios::binary);
	f << my_text;
	f.close();

	std::cout << "Алгоритм Шеннона-Фано" << std::endl;

	if (worker.run_encoding("task.txt", "compressed.bin")) {
		std::cout << "Файл закодирован" << std::endl;
		worker.print_table();
	}

	worker.run_decoding("compressed.bin", "restored.txt");

	std::ifstream f1("task.txt", std::ios::ate | std::ios::binary);
	std::ifstream f2("compressed.bin", std::ios::ate | std::ios::binary);

	double s1 = f1.tellg();
	double s2 = f2.tellg();

	std::cout << std::endl << "Результаты" << std::endl;
	std::cout << "Исходный размер: " << s1 << " байт" << std::endl;
	std::cout << "Сжатый размер: " << s2 << " байт" << std::endl;
	std::cout << "Коэффициент сжатия (больше - лучше): " << s1 / s2 << std::endl;

	std::cout << std::endl << "Декодированный текст лежит в restored.txt" << std::endl;

	return 0;
}