/***************************************************************************************************
=========================== ADAPTER DESIGN PATTERN (CODE EXPLANATION) =============================

We will explain the code in layers exactly how interviewer expects.

FLOW OF SYSTEM:

Raw Data
   |
   v
XmlDataProvider (creates XML)
   |
   v
XmlDataProviderAdapter
   |
   v
Client gets JSON


----------------------------------------------------------------------------------------------------
STEP 1 — TARGET INTERFACE
----------------------------------------------------------------------------------------------------
*/

class IReports {
public:
    virtual string getJsonData(const string& data) = 0;
};

/*
This is the interface CLIENT understands.

Client only knows:

"I will give raw data and get JSON"

Client does NOT know:
XML
XmlDataProvider
Legacy system

This abstraction is VERY IMPORTANT in design patterns.

INTERVIEW TIP:
Always program to interfaces, not implementations.

----------------------------------------------------------------------------------------------------
STEP 2 — ADAPTEE (LEGACY SYSTEM)
----------------------------------------------------------------------------------------------------
*/

class XmlDataProvider {
public:
    string getXmlData(const string& data) {

        size_t sep = data.find(':');

        string name = data.substr(0, sep);
        string id   = data.substr(sep + 1);

        return "<user>"
               "<name>" + name + "</name>"
               "<id>"   + id   + "</id>"
               "</user>";
    }
};

/*
This class already exists.

We CANNOT change it.

It returns XML.

Example input:

"Alice:42"

Output XML:

<user>
   <name>Alice</name>
   <id>42</id>
</user>

But the client expects JSON.

So we need an adapter.

----------------------------------------------------------------------------------------------------
STEP 3 — ADAPTER
----------------------------------------------------------------------------------------------------
*/

class XmlDataProviderAdapter : public IReports {

private:
    XmlDataProvider* xmlProvider;

public:

    XmlDataProviderAdapter(XmlDataProvider* provider) {
        this->xmlProvider = provider;
    }

    string getJsonData(const string& data) override {

        string xml = xmlProvider->getXmlData(data);

        size_t startName = xml.find("<name>") + 6;
        size_t endName   = xml.find("</name>");

        string name = xml.substr(startName, endName - startName);

        size_t startId = xml.find("<id>") + 4;
        size_t endId   = xml.find("</id>");

        string id = xml.substr(startId, endId - startId);

        return "{\"name\":\"" + name + "\", \"id\":" + id + "}";
    }
};

/*
This class is the core of the adapter pattern.

It does THREE things:

1️⃣ calls adaptee
2️⃣ converts data
3️⃣ returns expected format

Important:

Adapter implements Target interface.

This allows client to use it without knowing about XML provider.

----------------------------------------------------------------------------------------------------
STEP 4 — CLIENT
----------------------------------------------------------------------------------------------------
*/

class Client {
public:
    void getReport(IReports* report, string rawData) {

        cout << report->getJsonData(rawData);

    }
};

/*
Client only depends on:

IReports

It does NOT know about:

XmlDataProvider
XmlDataProviderAdapter

This ensures loose coupling.

----------------------------------------------------------------------------------------------------
STEP 5 — MAIN FUNCTION
----------------------------------------------------------------------------------------------------
*/

int main() {

    XmlDataProvider* xmlProv = new XmlDataProvider();

    IReports* adapter = new XmlDataProviderAdapter(xmlProv);

    string rawData = "Alice:42";

    Client* client = new Client();

    client->getReport(adapter, rawData);

}

/*
Execution flow:

Client
   |
calls
   v
Adapter.getJsonData()

Adapter
   |
calls
   v
XmlDataProvider.getXmlData()

XmlDataProvider
   |
returns XML
   v
Adapter converts XML → JSON
   |
returns JSON
   v
Client prints JSON

----------------------------------------------------------------------------------------------------
DRY RUN
----------------------------------------------------------------------------------------------------

Input:

rawData = "Alice:42"

STEP 1
------

Adapter calls:

xmlProvider->getXmlData("Alice:42")

STEP 2
------

Inside XmlDataProvider:

name = "Alice"
id   = "42"

XML generated:

<user><name>Alice</name><id>42</id></user>

STEP 3
------

Adapter extracts values:

name = Alice
id   = 42

STEP 4
------

Adapter builds JSON:

{"name":"Alice", "id":42}

STEP 5
------

Client prints:

Processed JSON: {"name":"Alice", "id":42}

----------------------------------------------------------------------------------------------------
KEY DESIGN PATTERN TAKEAWAY
----------------------------------------------------------------------------------------------------

Adapter acts as TRANSLATOR.

Without Adapter:

Client ←X→ XmlDataProvider

With Adapter:

Client → Adapter → XmlDataProvider

----------------------------------------------------------------------------------------------------
INTERVIEW LEVEL TAKEAWAY
----------------------------------------------------------------------------------------------------

Adapter is used when:

Old System Format != New System Format

Adapter converts data and allows systems to communicate
without modifying existing code.

***************************************************************************************************/