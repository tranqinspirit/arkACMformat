
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <map>

std::string title(std::string &, std::string, std::string &);
std::string importStart(std::string &);
std::string importEnd(std::string &, std::string);


int main(){

	std::ifstream importFile;
	importFile.open("arkImport.txt");

	std::ofstream outportFile;
	outportFile.open("arkImportFormatted.txt", std::ofstream::out | std::ofstream::trunc);

	std::string import;
	std::string titleLine;
	std::string modName;
	std::string filter;
	std::string filterFollow;

	std::map<int, std::string> filterList;
	int marker;

	for (int i = 0; std::getline(importFile, import); i++){
		

		if (import == "[Mod Name]" || import == "[Mod]"){
			std::getline(importFile, modName);
			i = i + 1;
		}

		if (iscntrl(import[0]) || isspace(import[0])){
			std::getline(importFile, filter);
			i++;
			if (!iscntrl(filter[0]) || !isspace(filter[0]) && isalpha(filter[0])){
				std::getline(importFile, filterFollow);
				i++;
				if (iscntrl(filterFollow[0]) || isspace(filterFollow[0])){
					marker = i - 1;
					filterList.insert(std::pair<int, std::string>(marker, filter));
				}
			}
		}
	}

	importFile.close();



	importFile.open("arkImport.txt");
	for (int i = 0; std::getline(importFile, import); i++){

		std::map<int, std::string>::iterator marker = filterList.begin();
		std::string currentFilter = marker->second;

		if ((i + 2) == (marker->first))
			++marker;


		if (import == "[Mod Name]" || import == "[Mod]" || import == modName || import == marker->second)
			import.clear();

		
		if (isblank(import[0])){
				import.clear();
			}
			

		if (isupper(import[0]) || isdigit(import[0])){
			title(modName, import, titleLine);
			outportFile << titleLine;
		}
		else {
			if (isalpha(import[0])) {
					importStart(import);
					outportFile << importEnd(import, currentFilter);
			}
		}
		//outportFile << "\n";
	}

	outportFile.close();
	importFile.close();
	return 0;
}


std::string title(std::string &modName, std::string import, std::string &titleLine){

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
	
	titleLine = modName + import;

return titleLine;
}


std::string importStart(std::string &import){

	std::size_t start = import.find_first_of("\"");
	import.erase(0, start); //gets rid of any pre-written spawn command formatting
	
return import;
} 


std::string importEnd(std::string &import, std::string filter){
		
	std::string importFormatted;
	std::size_t end = import.find_last_of("\"");
	std::string endLine = "|false|";

	import.erase(end + 1, std::string::npos);
	import.append("|");
	importFormatted = import + filter + endLine;
return importFormatted;
}
