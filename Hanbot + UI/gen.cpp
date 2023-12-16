#include <Authentication.h>
#include <iostream>
#include <skStr.h>


int main() {

    Authentication::AuthenticationInitialize();
    Authentication:: LicenseAuth();
    Security::checkForMonitoringTools();

    std::cout << skCrypt("Authentication Successful, waiting for League instances.\n").decrypt();
    League::waitForLeagueOfLegends();
    return 0;

}