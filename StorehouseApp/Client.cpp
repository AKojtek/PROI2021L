#include "Client.h"

std::istream& operator>> (std::istream& is, std::vector<Client>& clients) {
    std::string line;
    while (is.peek() != EOF) {
        std::getline(is, line);
        std::istringstream iss(line);
        Client client;
        iss >> client;
        clients.emplace_back(client);
    }
    return is;
}

std::ostream& operator<< (std::ostream& os, const std::vector<Client>& clients)
{
    for (auto& client : clients) {
        os << client;
    }
    return os;
}

std::istream& operator>> (std::istream& is, Client& client) {
    char curr_char;
    is >> client.m_id;
    is.get(curr_char);
    while (curr_char == ' ' || curr_char == '\t' || curr_char == '\n')
        is.get(curr_char);
    if (curr_char == '[')
    {
        client.m_name = "";
        is.get(curr_char);
        while (curr_char != ']')
        {
            client.m_name += curr_char;
            is.get(curr_char);
        }
    }
    else
    {
        is.unget();
        is >> client.m_name;
    }

    is.get(curr_char);
    while (curr_char == ' ' || curr_char == '\t' || curr_char == '\n')
        is.get(curr_char);
    if (curr_char == '[')
    {
        client.m_city = "";
        is.get(curr_char);
        while (curr_char != ']')
        {
            client.m_city += curr_char;
            is.get(curr_char);
        }
    }
    else
    {
        is.unget();
        is >> client.m_city;
    }
    is >> client.m_phone;
    return is;
}

std::ostream& operator<< (std::ostream& os, const Client& client)
{
    os << client.m_id << '\t' << client.m_name << '\t' << client.m_city << '\t' <<
        client.m_phone << '\n';
    return os;
}

std::string prepareForFile (const Client& client)
{
    std::string out = std::to_string(client.m_id) + "\t[" + client.m_name +
        "]\t[" + client.m_city + "]\t" + client.m_phone + '\n';
    return out;
}

bool operator< (const Client& client, const Client& other) {
    return client.getClientID() < other.getClientID();
}

Client::Client(int id, std::string name, std::string city, std::string phone) {
    m_id = id;
    m_name = std::move(name);
    m_city = std::move(city);
    m_phone = std::move(phone);
}

int Client::getClientID() const {
    return m_id;
}


std::string Client::getName() const {
    return m_name;
}

std::string Client::getCity() const {
    return m_city;
}

std::string Client::getPhone() const {
    return m_phone;
}

