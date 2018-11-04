#pragma once
#ifndef SEARCH_H
#define SEARCH_H
#include "Date.h"
#include <Windows.h>
#include <string>
#include <vector>
#include <list>
#include <utility>
int getNumberOfPages(int);

void drawPage(int, std::list<Date>::iterator&, std::list<Date>::iterator&, int, int);

void drawSearchParameters(Date&,Date&,unsigned char,unsigned int, int, int);
std::pair<Period,unsigned int> getSearchParameters();
void searchPeriod(Period&);
void searchModuleMainLoop();


#endif