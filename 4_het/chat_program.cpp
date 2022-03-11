#include <algorithm>
#include <list>
#include <string>
#include <vector>

using namespace std;

class User;
class Message;
class Conversation;

// placeholder namespace for the networking interface, which is not part of this example
namespace ClientHandler {

// sends message to recipient's chat client
// conv needed to send its id to the client
void sendMsg(const Message* msg, const User* recipient, const Conversation* conv);

// sends metadata of conversation to recipient's client
void sendInfo(const User* recipient, const Conversation* conv);

// gets called when message is received from a client
// sender was retrieved by UserManager::getUserByName
// conv was retrieved by User::getConversation
void onMsgReceived(User* sender,
    const string& msgText,
    Conversation* conv)
{
    if (!sender) return;
    conv->forwardMsg(new Message(sender, msgText));
}

// u1 and u2 were retrieved by UserManager::getUserByName
void startPrivateConversation(User* u1, User* u2)
{
    if (!u1 || !u2) return;
    auto conv = new PrivateConversation(u1, u2);
    u1->enterConversation(conv);
    u2->enterConversation(conv);
}

// creator was retrieved by UserManager::getUserByName
void createGroupChat(User* creator)
{
    if (!creator) return;
    auto conv = new GroupConversation(creator);
    creator->enterConversation(conv);
}

// invited was retrieved by UserManager::getUserByName
// group was retrieved by User::getConversation
bool inviteToGroup(User* invited, GroupConversation* group)
{
    if (!invited) return;
    invited->enterConversation(group);
    group->addMember(invited);
}

} // namespace ClientHandler

class User {
    string username;
    vector<Conversation*> openConvs;

public:
    User(const string& username)
        : username(username)
    {
    }
    const string& getUsername() const { return username; }
    void enterConversation(Conversation* conv)
    {
        ClientHandler::sendInfo(this, conv);
        openConvs.push_back(conv);
    }
    // lookup should be based on Conversation ID but keeping it simple now
    Conversation* getConversation(size_t index) const
    {
        return openConvs[index];
    }
};

class UserManager {
    list<User*> users;

    list<User*>::const_iterator findUserByName(const string& username) const
    {
        auto namecmp = [username](User* u) { return u->getUsername() == username; };
        return find_if(users.begin(), users.end(), namecmp);
    }

public:
    // gets called by ClientHandler when a client tries to register a user
    bool registerUser(const string& username)
    {
        bool found = findUserByName(username) != users.end();
        if (found)
            return false;
        users.push_back(new User(username));
        return true;
    }
    bool unregisterUser(const string& username)
    {
        auto iter = findUserByName(username);
        if (iter == users.end())
            return false;
        users.erase(iter);
        return true;
    }
    // returns nullptr if not found
    User* getUserByName(const string& username) const
    {
        auto iter = findUserByName(username);
        if (iter == users.end())
            return nullptr;
        return *iter;
    }
};

class Message {
    User* author;
    string content;

public:
    Message(User* author, const string& content)
        : author(author)
        , content(content)
    {
    }
    const User* getAuthor() const { return author; }
};

class Conversation {
protected:
    vector<Message*> msgs;

public:
    virtual ~Conversation() = 0;
    // stores and forwards msg from a user to other members of the conversation
    virtual void forwardMsg(Message* msg) { msgs.push_back(msg); }
};

class PrivateConversation : public Conversation {
    User* users[2];

public:
    PrivateConversation(User* u1, User* u2)
        : users{u1, u2}
    {
    }
    void forwardMsg(Message* msg) override
    {
        ClientHandler::sendMsg(msg, msg->getAuthor() == users[0] ? users[1] : users[0], this);
        Conversation::forwardMsg(msg);
    }
};

class GroupConversation : public Conversation {
    vector<User*> members;

public:
    GroupConversation(User* creator);
    void addMember(User* toAdd)
    {
        // send old messages to new member
        for (auto msg : msgs) {
            ClientHandler::sendMsg(msg, toAdd, this);
        }
        members.push_back(toAdd);
    }
    void forwardMsg(Message* msg) override
    {
        for (auto member : members) {
            if (member != msg->getAuthor())
                ClientHandler::sendMsg(msg, member, this);
        }
        Conversation::forwardMsg(msg);
    }
};

