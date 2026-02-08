#include "System.h"




void System::Run() {

	while (true) {
		int status = Foptimizer.MainMenu();
		if (status == -1) {
			Boptimizer.Save_Database();
			return;
		}
		while (true) {
			status = Foptimizer.ViewUserDashboard();
			if (status == -1) {
				Boptimizer.Save_Database();
				break;
			}

		}


	}
}