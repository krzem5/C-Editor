#ifdef _MSC_VER
#include <windows.h>
#include <conio.h>
#endif
#include <editor.h>
#include <stdio.h>



#ifdef _MSC_VER
int main(int argc,const char** argv){
	SetConsoleOutputCP(CP_UTF8);
	HANDLE hi=GetStdHandle(STD_INPUT_HANDLE);
	HANDLE ho=GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD im;
	GetConsoleMode(hi,&im);
	SetConsoleMode(hi,ENABLE_WINDOW_INPUT|ENABLE_MOUSE_INPUT|ENABLE_VIRTUAL_TERMINAL_INPUT);
	DWORD om;
	GetConsoleMode(ho,&om);
	SetConsoleMode(ho,ENABLE_PROCESSED_OUTPUT|ENABLE_VIRTUAL_TERMINAL_PROCESSING|DISABLE_NEWLINE_AUTO_RETURN);
	CONSOLE_CURSOR_INFO ci;
	GetConsoleCursorInfo(ho,&ci);
	ci.bVisible=0;
	SetConsoleCursorInfo(ho,&ci);
	CONSOLE_SCREEN_BUFFER_INFO sbi;
	GetConsoleScreenBufferInfo(ho,&sbi);
	DWORD tmp;
	COORD z={
		0,
		0
	};
	FillConsoleOutputCharacterA(ho,' ',sbi.dwSize.X*sbi.dwSize.Y,z,&tmp);
	FillConsoleOutputAttribute(ho,7,sbi.dwSize.X*sbi.dwSize.Y,z,&tmp);
	editor_t e;
	init_editor(&e);
	set_window_size(&e,sbi.srWindow.Right+1,sbi.srWindow.Bottom+1);
	if (argc>1){
		open_file(&e,argv[1]);
	}
	while (e.fl&EDITOR_FLAG_OPEN){
		render_editor(&e);
		if (_kbhit()){
			int k=_getch();
			if (k>31&&k<127){
				type_key(&e,k);
			}
			else if (k==0x03){
				type_key(&e,EDITOR_KEY_CTRL_C);
			}
			else if (k==0x0d){
				type_key(&e,EDITOR_KEY_ENTER);
			}
			else if (k==0x1b){
				if (_kbhit()){
					k=_getch();
					if (k=='['){
						k=_getch();
						if (k=='1'){
							k=_getch();
							if (k==';'){
								k=_getch();
								if (k=='5'){
									k=_getch();
									if (k=='A'){
										type_key(&e,EDITOR_KEY_CTRL_UP);
									}
									else if (k=='B'){
										type_key(&e,EDITOR_KEY_CTRL_DOWN);
									}
									else if (k=='C'){
										type_key(&e,EDITOR_KEY_CTRL_RIGHT);
									}
									else if (k=='D'){
										type_key(&e,EDITOR_KEY_CTRL_LEFT);
									}
								}
							}
						}
						else if (k=='3'){
							k=_getch();
							if (k=='~'){
								type_key(&e,EDITOR_KEY_DELETE);
							}
						}
						else if (k=='5'){
							k=_getch();
							if (k=='~'){
								type_key(&e,EDITOR_KEY_PAGE_UP);
							}
							else if (k==';'){
								k=_getch();
								if (k=='5'){
									k=_getch();
									if (k=='~'){
										type_key(&e,EDITOR_KEY_PAGE_CTRL_UP);
									}
								}
							}
						}
						else if (k=='6'){
							k=_getch();
							if (k=='~'){
								type_key(&e,EDITOR_KEY_PAGE_DOWN);
							}
							else if (k==';'){
								k=_getch();
								if (k=='5'){
									k=_getch();
									if (k=='~'){
										type_key(&e,EDITOR_KEY_PAGE_CTRL_DOWN);
									}
								}
							}
						}
						else if (k=='A'){
							type_key(&e,EDITOR_KEY_UP);
						}
						else if (k=='B'){
							type_key(&e,EDITOR_KEY_DOWN);
						}
						else if (k=='C'){
							type_key(&e,EDITOR_KEY_RIGHT);
						}
						else if (k=='D'){
							type_key(&e,EDITOR_KEY_LEFT);
						}
						else if (k=='H'){
							type_key(&e,EDITOR_KEY_HOME);
						}
						else if (k=='F'){
							type_key(&e,EDITOR_KEY_END);
						}
					}
					while (_kbhit()){
						_getch();
					}
				}
				else{
					type_key(&e,EDITOR_KEY_ESCAPE);
				}
			}
			else if (k==0x7f){
				type_key(&e,EDITOR_KEY_BACKSPACE);
			}
		}
	}
	free_editor(&e);
	SetConsoleMode(hi,im);
	SetConsoleMode(ho,om);
	return 0;
}
#else
#error Unimplemented!
#endif
