#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <vector>

using sdvar = std::variant<std::string, double>; // ezek utan sdvar tipus is hasznalhato

class Document {
    const std::string name;
    double sizeInMbs;
public:
    Document(std::string nm, double sz) : name{ nm }, sizeInMbs{ sz } {}
    virtual ~Document() {};
    const std::string& getName() { return name; }
    double getSize() { return sizeInMbs; }
    virtual void printDetails() = 0;
};

class TextDocument : public Document {
public:
    // a konstruktort valositsa meg!
    TextDocument(std::string nm, double sz) : Document(nm, sz) {}
    void printDetails() override {
        std::cout << "Text document entitled: " << getName() << " - with size of " << getSize() << "Mb" << std::endl;
    }
};

class AudioFile : public Document {
    const std::string format;
public:
    // a konstruktort valositsa meg!
    AudioFile(std::string nm, std::string f, double sz) : Document(nm, sz), format(f) {}
    void printDetails() override {
        std::cout << format << " file entitled: " << getName() << " - with size of " << getSize() << "Mb" << std::endl;
    }
};

class DocumentFactory {
private:
    DocumentFactory() {}
public:
    // implementalja NewDocument() metódust ugy hogy a pelda kod lefusson
    // az elso argumentum string, ertek ami lehet "text" vagy "music", es ettol fugg a letrejovo document tipusa
    // a masodik argumentum a konstruktornak tovabbitando sdvar ertekeket tartalmazo vector
    static Document* NewDocument(std::string type, std::vector<sdvar> arglist) {
        if (type == "music" && arglist.size() == 3) {
            return new AudioFile(std::get<std::string>(arglist[0]), std::get<std::string>(arglist[1]), std::get<double>(arglist[2]));
        } 
        if (type == "text" && arglist.size() == 2) {
            return new TextDocument(std::get<std::string>(arglist[0]), std::get<double>(arglist[1]));
        } return NULL;
    }
};

int main() {
    Document* af1 = DocumentFactory::NewDocument("music", {sdvar("Back Chat"), sdvar("mp3"), sdvar(3.41)}); // a variant vektort az initializer-list hozza letre!
    Document* af2 = DocumentFactory::NewDocument("music", {sdvar("All you need is love"), sdvar("flac"), sdvar(5.89)});
    Document* tf1 = DocumentFactory::NewDocument("text", {sdvar("Nobel.txt"), sdvar(2.20)});
    Document* af3 = DocumentFactory::NewDocument("music", {sdvar("Some audio"), sdvar(5.00)}); // nincs eleg argumentum!
    if (af1) { af1->printDetails(); }
    else { std::cout << "af1: cannot create based on arguments" << std::endl; }
    if (af2) { af2->printDetails(); }
    else { std::cout << "af2: cannot create based on arguments" << std::endl; }
    if (tf1) { tf1->printDetails(); }
    else { std::cout << "tf1: cannot create based on arguments" << std::endl; }
    if (af3) { af3->printDetails(); }
    else { std::cout << "af3: cannot create based on arguments" << std::endl; }

    dynamic_cast<AudioFile*>(af1)->printDetails();
    dynamic_cast<TextDocument*>(tf1)->printDetails();

    delete af1;
    delete af2;
    delete tf1;
    
    return 0;
}
