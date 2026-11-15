export module StudentModel;
import <string>;

export class Student {
private:
	std::string name;
	int grade;

public:
	Student(std::string nam) {
		name = nam;
		grade = 0;
	}

	void setGrade(int gr) {
		grade = gr;
	}

	int getGrade() {
		return grade;
	}
};

