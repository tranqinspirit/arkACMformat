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
	std::map<int, std::string> filterList;

	std::string import;
	std::string filter;
	std::string filterFollow;

	int marker;

	importFile.open("arkImport.txt");
	//getting the parts of our filters for later
	 for (int i = 0; std::getline(importFile, import); i++){
		if (iscntrl(import[0]) || isspace(import[0])){
			std::getline(importFile, filter);
			i++;
			if (!iscntrl(filter[0]) || !isspace(filter[0]) && isalpha(filter[0])){ //OCD demands only one space between entries and filters
				if (islower(filter[0]))
					continue;
				else
				std::getline(importFile, filterFollow);
				i++;
				if (iscntrl(filterFollow[0]) || isspace(filterFollow[0])){
						marker = i - 1;
						filterList.insert(std::pair<int, std::string>(marker, filter));
				}
			}
		}
	}
	importFile.close(); //close stream from when we got filters

	importFile.open("arkImport.txt");
	//getting mod name so we can put it at the start of our ofstream
	std::string modName;
	while (std::getline(importFile, import)){
		if (import == "[Mod Name]" || import == "[Mod]"){
			std::getline(importFile, modName);
			importFile.close();
		}
	}

	if(!importFile.is_open())
	importFile.open("arkImport.txt");
		
	std::ofstream outportFile;
	outportFile.open("arkImportFormatted.txt", std::ofstream::out | std::ofstream::trunc);

	std::string titleLine;
	std::string currentFilter;
	std::string formattedOutport;

	for (int j = 0; std::getline(importFile, import); j++){

		for (std::map<int, std::string>::iterator filterFormat = filterList.begin(); filterFormat != filterList.end(); ++filterFormat){
			if (j == filterFormat->first)
				currentFilter = filterFormat->second;
		}

		if (import == "[Mod Name]" || import == "[Mod]" || import == modName || import == currentFilter || isblank(import[0]) || isspace(import[0]) || iscntrl(import[0])) //cleans tags and their appropriate lines from our output
			import.clear();

		else {

			if (isupper(import[0]) || isdigit(import[0])){ //grabbing line preceeding our spawn code
				title(modName, import, titleLine);
				outportFile << titleLine;
			}

			else {
				importStart(import);
				formattedOutport = importEnd(import, currentFilter);

				if (importFile.peek() == EOF){
					formattedOutport.pop_back();
					outportFile << formattedOutport;
				}
				else
					outportFile << formattedOutport;
			}
		}
	}
	outportFile.close();
	importFile.close();

	return 0;
}


std::string title(std::string &modName, std::string import, std::string &titleLine){

	int adjust = 0;
	if (!isalpha(import[0])){
		for (int i = 0; !isblank(import[i]); i++){
			adjust++;
		}
		import.erase(0, adjust + 1);
	} //clears out any quantities of the item we're formatting

	import.insert(0, "|"); //adds separator to start of string according to ACM's formatting rules ( | between mod name and entry name)
	if (ispunct(import.back()))
		import.pop_back();

	import.append("|"); //adds separator to end of string according to ACM's formatting rules ( | between entry name and blueprint path)
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
	import.erase(end + 1, std::string::npos); //gets rid of anything following the blueprint path
	import.append("|");
	std::string endLine = "|false|";
	importFormatted = import + filter + endLine;

return importFormatted;
}
