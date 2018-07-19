#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>

class FechayHora{
private:
	int year;
	int month;
	int day;
	int hs;
	int min;
	int sec;

public:
	FechayHora(int n){
		/* Obtener el tiempo actual*/
    	time_t  now = time(0);
    	/* Obtengo la estructura tm*/
    	struct tm * t = localtime(&now);
   		this->year = 1900+ t->tm_year;
    	this->month = t->tm_mon +1;
    	this->day = t->tm_mday;
    	this->hs = t->tm_hour;
    	this->min = t->tm_min;
    	this->sec =  t->tm_sec;	
	}

	/*debe tener el formato  dia/mes/año hora:min:seg*/
	FechayHora(char * localdaytime){
		sscanf(localdaytime, "%d/%d/%d %d:%d:%d", &this->day , &this->month, &this->year, &this->hs, &this->min, &this->sec);

	}

	//contructor por copia
	FechayHora(const FechayHora &other){
		this->year = other.year;
    	this->month = other.month;
    	this->day = other.day;
    	this->hs = other.hs;
    	this->min = other.min;
    	this->sec =  other.sec;	
	}

	FechayHora& operator =(const FechayHora &other){
		this->year = other.year;
    	this->month = other.month;
    	this->day = other.day;
    	this->hs = other.hs;
    	this->min = other.min;
    	this->sec =  other.sec;
    	return (*this);
	}

	int get_year() const {
		return this->year;
	}

	int get_month() const {
		return this->month;
	}

	int get_day() const {
		return this->day;
	}

	int get_hs() const {
		return this->hs ;
	}

	int get_min() const {
		return this->min ;
	}

	int get_sec() const {
		return this->sec ;
	}



	bool operator ==(const FechayHora &other) const{
		if(this->year != other.year){
			return false;
		}
    	if(this->month !=  other.month){
			return false;
		}
    	if(this->day !=  other.day){
			return false;
		}
    	if(this->hs !=  other.hs){
			return false;
		}
    	if(this->min !=   other.min){
			return false;
		}
    	if(this->sec !=   other.sec){
			return false;
		}
    	return true;
	}

	bool operator <(const FechayHora &other) const{
		if(this->year < other.year){
			return true;
		}
    	if(this->month < other.month){
			return true;
		}
    	if(this->day < other.day){
			return true;
		}
    	if(this->hs < other.hs){
			return true;
		}
    	if(this->min < other.min){
			return true;
		}
    	if(this->sec < other.sec){
			return true;
		}
    	return false;

	}

	operator int () const{
		unsigned long sec = (((((this->year*12 +this->month)*30+this->day)*24+this->hs)*60+this->min)*60+this->sec);
		return sec;
	}

};

std::ostream& operator << (std::ostream & out, const FechayHora & fecha){
	out << fecha.get_day() << "/" << fecha.get_month()  << "/" << fecha.get_year()  << " "//
	<< fecha.get_hs() << ":" <<fecha.get_min() << ":" << fecha.get_sec();
	 return out;	
}


int main(int argc, char *argv[]){
	FechayHora hoy(1);
	char fecha_str[] = "13/06/2018 16:08:21";
	FechayHora fecha(fecha_str);
	FechayHora hace_mucho = fecha;

	if(fecha < hoy){
		printf("haceAños es menor a hoy\n");
	}

	if(hoy == hoy){
		printf("hoy es igual a hay\n");
	}
	printf("fecha en segundos = %u\n",(int) hoy );

	std::cout <<"la fecha de hoy es "<< hoy <<"\n";


}				