#ifndef PROJECT
#define PROJECT

struct Project {
    int id;
    const string name;

    Project(int id, const string& name) : id(id), name(name) {
        cout << toString() << " has been started.\n";
    }
    ~Project() {
        cout << toString() << " has been abandoned.\n";
    }
    string toString() const {
        return "Project '" + name + "' (ID: " + to_string(id) + ")";
    }
};

class Manager {
    const string name;
    map<int, shared_ptr<Project>> projects;
public:
    Manager(const string& name); // TODO
    string GetName() const { return name; }
    void StartProject(int id, const string& name); // TODO
    
    bool JoinProject(weak_ptr<Project> p); // TODO
   
    void AbandonProject(int id); // TODO
  
    weak_ptr<Project> GetProject(int id) const; // TODO
};

#endif
