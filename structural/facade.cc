#include <iostream>
#include <string>

/* Subsystems */

class Doctor {
public:
    void consult() {
        std::cout << "Doctor consultation\n";
    }

    void checkReports() {
        std::cout << "Doctor checking reports\n";
    }

    void prescribeMedicine() {
        std::cout << "Doctor prescribing medicine\n";
    }
};

class Dietitian {
public:
    void checkReports() {
        std::cout << "Dietitian checking reports\n";
    }

    void provideDietPlan() {
        std::cout << "Dietitian providing diet plan\n";
    }
};

class Receptionist {
public:
    void registerPatient() {
        std::cout << "Patient registered\n";
    }

    void collectPayment() {
        std::cout << "Payment collected\n";
    }
};

/* Facade */

class HospitalFacade {
public:
    HospitalFacade(Doctor& doc, Dietitian& diet, Receptionist& recp)
        : doctor_(doc), dietitian_(diet), receptionist_(recp) {}

    void fullBodyCheckup() {
        receptionist_.registerPatient();
        doctor_.consult();
        doctor_.checkReports();
        doctor_.prescribeMedicine();
        dietitian_.checkReports();
        dietitian_.provideDietPlan();
        receptionist_.collectPayment();
    }

private:
    Doctor& doctor_;
    Dietitian& dietitian_;
    Receptionist& receptionist_;
};

/* Client */

int main() {
    Doctor doctor;
    Dietitian dietitian;
    Receptionist receptionist;

    HospitalFacade hospital(doctor, dietitian, receptionist);
    hospital.fullBodyCheckup();

    return 0;
}
