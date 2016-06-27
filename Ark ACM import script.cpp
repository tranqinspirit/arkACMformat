
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>


std::string title(std::string, std::string &);
std::string importStart(std::string &);
std::string importEnd(std::string &);



int main(){

	std::string import;
	std::string titleLine;
	
	std::ifstream importFile;
	importFile.open("arkImport.txt");

	std::ofstream outportFile;
	outportFile.open("arkImportFormatted.txt", std::ofstream::out | std::ofstream::trunc);


	while (std::getline(importFile, import)){
		if (isblank(import[0])){
			import.clear();
		}

		if (isupper(import[0]) || isdigit(import[0])){
			title(import, titleLine);
			outportFile << titleLine;
		}
		else {
			if (isalpha(import[0])) {
				importStart(import);
				outportFile << importEnd(import);
				outportFile << "\n";
			}
		}

	}

	outportFile.close();
	importFile.close();
	return 0;
}


std::string title(std::string import, std::string &titleLine){

	int adjust = 0;
	if (isdigit(import[0])){
		for (int i = 0; !isblank(import[i]); i++){
			adjust++;
		}
		import.erase(0, adjust + 1);
	} //clears out any quantities of the item we're formatting

	import.insert(0, "|"); //adds separator to start of string according to ACM's formatting rules ( | between mod name and item)
	if (ispunct(import.back()))
		import.pop_back();

	import.append("|"); //adds separator to end of string according to ACM's formatting rules ( | between item and blueprint path)
	
	titleLine = import;

return titleLine;
}


std::string importStart(std::string &import){

	std::size_t start = import.find_first_of("\"");
	import.erase(0, start); //gets rid of any pre-written spawn command formatting
	
return import;
} 


std::string importEnd(std::string &import){
		
	std::string importFormatted;
	std::size_t end = import.find_last_of("\"");
	std::string endLine = "||false|";

	import.erase(end + 1, std::string::npos);
	importFormatted = import + endLine;
	
return importFormatted;
}
