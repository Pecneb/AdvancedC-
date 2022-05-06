// Konstruktor, eltárolja a Manager nevét, inicializálja az adatstruktúrát
Manager::Manager(const string& name) : name(name){}

// Létrehoz egy egy új projektet a megadott ID-val és névvel, és eltárolja a Managerhez
// Feltételezhető, hogy minden projektnek egyedi ID-t adnak meg
void Manager::StartProject(int id, const string& name) {
    std::shared_ptr<Project> newProject(new Project(id, name));
    projects.insert( pair<int, shared_ptr<Project>>(id, newProject) );
}

// Eltárolja, hogy a Manager részt vesz a megadott projektben
// Ha a projekt már megszűnt, adjon vissza hamis értéket, különben igazat
bool Manager::JoinProject(weak_ptr<Project> p) {
    if ( p.expired() ) return 0;
    if ( shared_ptr<Project> runningProject = p.lock() ) {
        projects.insert( pair<int, shared_ptr<Project>>(runningProject->id, runningProject) );
        return 1;
    } else {
       return 0;
    }
}

// Elhagyja a megadott ID-jú projektet, ami meg is szűnik, ha más már nem dolgozik rajta
// Ha a Manager nem dolgozik az adott ID-jú projekten, ne történjen semmi sem
void Manager::AbandonProject(int id) {
    map<int, shared_ptr<Project>>::iterator it = projects.find(id);
    if ( it != projects.end() ) (it->second).reset();
}

// Adjon vissza egy pointert a Manager adott ID-jú projektjére
// Ha az ID nem található, adjon vissza üres weak_ptr-t
weak_ptr<Project> Manager::GetProject(int id) const {
    map<int, shared_ptr<Project>>::const_iterator it = projects.find(id);
    weak_ptr<Project> wp;
    if ( it != projects.end() ) wp = it->second;
    return wp;
}
