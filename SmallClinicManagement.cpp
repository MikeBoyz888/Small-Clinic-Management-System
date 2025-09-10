#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Appointment{
    private:
    string date;
    string time;
    string reason;
    string status; //bao gồm "Scheduled", "Completed" và "Canceled"
    string patientID;
    string doctorID;

    public:
    Appointment(string d, string t, string r, string pID, string dID) : date(d), time(t), reason(r), status("Scheduled"), patientID(pID), doctorID(dID) {}

    void setStatus(string newStatus) {
        if (newStatus == "Scheduled" || newStatus == "Completed" || newStatus == "Canceled") {
            status = newStatus;
            cout << "Appointment status updated to: " << status << endl;
        } else {
            cout << "Error: Invalid status!" << endl;
        }
    }

    void displayDetail() {
        cout << "Appointment: " << endl;
        cout << "Date: " << date << endl;
        cout << "Time: " << time << endl; 
        cout << "Reason: " << reason << endl;
        cout << "Status: " << status << endl;
        cout << "PatientID: " << patientID << endl;
        cout << "DoctorID: " << doctorID << endl;
    }

    string getPatientID(){
        return patientID;
    }

    string getDoctorID(){
        return doctorID;
    }
};

class Patient{
    protected:
    string id;
    string name;
    int age;
    vector<string> medicalHistory; //danh sách đến khám trong quá khứ

    public:
    Patient(string i, string n, int a) : id(i), name(n), age(a){} //Constructor để tạo 1 bệnh nhân

    virtual void scheduleAppointment(Appointment apm) {
        cout << "Scheduled appointment for patient " << name << endl;
    }

    void updateMedicalHistory(string visit){ //visit xem như là 1 lần khám
        medicalHistory.push_back(visit); // push back thêm 1 phần tử mới vào cuối danh sách của vector
        cout << "Medical history updated for patient " << name << endl;
    }

    virtual void displayInfo(){
        cout << "Patient ID:" << id << endl;
        cout << "Patient Name:" << name << endl;
        cout << "Patient Age:" << age << endl;
        cout << "Medical History: ";
        if (medicalHistory.empty()) {
            cout << "No records";
        } else {
            for (string v : medicalHistory) {
                cout << v << "; ";
            }
        }
        cout << endl;
    }

    string getID(){
        return id; //get patient ID
    }
};

class ChronicPatient : public Patient{
    private:
    string conditionType;
    string lastCheckupDate;

    public:
    ChronicPatient(string i, string n, int a, string cType, string lastCheck) : Patient(i, n, a), conditionType(cType), lastCheckupDate(lastCheck) {}

    void scheduleAppointment(Appointment apm) override { //override scheduleAppointment ghi đè lên phiên bản của Patient + thêm lần khám trước
        cout << "Scheduled frequent checkup for patient " << name << " (Last checkup: " << lastCheckupDate << ")" << endl;
    }

    void displayInfo() override {
        Patient::displayInfo();
        cout << "Condition: " << conditionType << endl;
        cout << "Last Checkup: " << lastCheckupDate << endl;
    }
};

class Doctor{
    private:
    string id;
    string name;
    string specialty;
    vector<Appointment> appointments; //Danh sách appointment

    public:
    Doctor(string i, string n, string s) : id(i), name(n), specialty(s) {}

    void assignAppointment(Appointment apm) {
        if (apm.getDoctorID() == id) {
            appointments.push_back(apm);
            cout << "Appointment assigned to Dr. " << name << endl;
        } else {
            cout << "Error: Appointment not with this doctor!" << endl;
        }
    }

    void updateAppointmentStatus(int index, string newStatus) {
        if (index >= 0 && index < appointments.size()) { //index là số nguyên chỉ vị trí của 1 cuộc hẹn khám trong danh sách Appointment
            appointments[index].setStatus(newStatus);
        } else {
            cout << "Error: Invalid appointment!" << endl;
        }
    }

    void displayInfo() {
        cout << "Doctor ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Specialty: " << specialty << endl;
        cout << "Appointments: ";
        if (appointments.empty()) {
            cout << "None";
        } else {
            cout << endl;
            for (size_t i = 0; i < appointments.size(); ++i) {
                cout << " [" << i << "] ";
                appointments[i].displayDetail();
            }
        }
        cout << endl;
    }

    string getID(){
        return id;
    }
};

int main(){
    Patient patient1("P123", "Mai Dang Quang", 24);
    ChronicPatient chronic1("P345", "Nguyen Thi D", 45, "Diabetes", "08/09/2025");
    Doctor doctor1("D011", "Huynh Xuan Phung", "Khoa noi tiet");

    Appointment apm1("09/09/2025", "10:00AM", "Kham tong quat", "P123", "D011");
    Appointment apm2("13/09/2025", "15:00PM", "Kiem tra dinh ky", "P345", "D011");

    cout << "Information------------------------" << endl;
    patient1.displayInfo();
    chronic1.displayInfo();
    doctor1.displayInfo();

    cout << "Appointment Info-------------------" << endl;
    patient1.scheduleAppointment(apm1);
    chronic1.scheduleAppointment(apm2);

    cout << "Update Appointment Status----------" << endl;
    doctor1.assignAppointment(apm1); //thêm để gán cuộc hẹn cho bác sĩ
    doctor1.assignAppointment(apm2);
    doctor1.updateAppointmentStatus(0, "Completed"); // 0 là vị trí đầu tiên trong danh sách appointment tương ứng apm1
    doctor1.updateAppointmentStatus(1, "Canceled");

    cout << "Uppdate Medical History------------" << endl;
    patient1.updateMedicalHistory("09/09/2025; Kham tong quat; Binh thuong");
    chronic1.updateMedicalHistory("13/09/2025; Cap them thuoc");

    cout << "Information Updated----------------" << endl;
    patient1.displayInfo();
    chronic1.displayInfo();
    doctor1.displayInfo();

    system("pause"); // tạm dừng chương trình tránh cmd bị tắt

    return 0;
}