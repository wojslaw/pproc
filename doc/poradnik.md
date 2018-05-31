

W wyniku przyjętej konwencji, liczby są zapisywane w postaci hexadecymalnej (base-16), gdzie przed liczbą znajduje się symbol "0x", oznaczający liczbę hexadecymalną w standardzie języka C. Jako domyślne są uznawane stałe 8-bitowe, czyli 2 cyfry zapisu hexadecymalnego:
np.: 0x02 0x55

Wyjątkie są adresy, które są dwubajtowe, a więc 4 cyfrowe w zapisie hexadecymalnym: np. 
	0x5043

Jako oznaczenie "pod adresem `X` znajduje się wartość `Y` wykorzystywany jest znak `@` przed wartością adresu:
	@0x5000 : 0x10	- w komórce pamięci pod adresem 0x5000 znajduje się wartość 0x10
	@0x0705 : 0x41  - w komórce pamięci pod adresem 0x0705 znajduje się wartość 0x41


Stament zaczynający się od znaku `#` oznacza dyrektywy kompilatora definiujące makra do adresów bądź stałych numerycznych.
	`(#defad var1)` - definicja adresu o etykiecie "var1"
	`(#defconst con1 0x55)` - definicja stałej numerycznej o etykiecie "con1" oraz wartości 0x55
