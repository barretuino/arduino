/*
Copyright 2010 Eric C. Gionet <lavco_eg@hotmail.com>
// ******************************************************
// implementation concept
// ******************************************************/
static byte ip[] = { 192, 168, 2, 64 };
static byte gateway[] = { 192, 168, 2, 1 };
static byte subnet[] = { 255, 255, 255, 0 };

// SNMP Agent - basic credentials
char getCommName[] PROGMEM   = "public";
char setCommName[] PROGMEM   = "private";
//
// RFC1213-MIB OIDs
char sysDescr[] PROGMEM        = "1.3.6.1.2.1.1.1.0";  // read-only  (DisplayString)
char sysObjectID[] PROGMEM   = "1.3.6.1.2.1.1.2.0";  // read-only  (ObjectIdentifier)
char sysUpTime[] PROGMEM     = "1.3.6.1.2.1.1.3.0";  // read-only  (TimeTicks)
char sysContact[] PROGMEM      = "1.3.6.1.2.1.1.4.0";  // read-write (DisplayString)
char sysName[] PROGMEM        = "1.3.6.1.2.1.1.5.0";  // read-write (DisplayString)
char sysLocation[] PROGMEM     = "1.3.6.1.2.1.1.6.0";  // read-write (DisplayString)
char sysServices[] PROGMEM    = "1.3.6.1.2.1.1.7.0";  // read-only  (Integer)
//
//
/* RFC1213 local values */
char locDescr[] PROGMEM      = "Agentuino, a light-weight SNMP Agent.";  // read-only (static)
char locObjectID[] PROGMEM   = "1.3.6.1.3.2009.0";                       // read-only (static)
long locUpTime              	   = 0;                                        // RTC is needed for this unless the NTP Time library is used
char locContact[20]          = "Eric Gionet";
char locName[20]             = "Agentuino";
char locLocation[20]         = "Nova Scotia, CA";
short locServices PROGMEM    = 7;                                        // read-only (static)

Agentiuno agent = Agentuino();

SNMP_SESSION session;

pduReceived() {
	SNMP_PDU request;
	SNMP_PDU response;
	//
	agent.requestPdu(request);
	//
	// process request
	//
	agent.responsePdu(response);
	//
	agent.freePdu(request);
	agent.freePdu(response);
}

setup() {
	Ethernet.begin(mac, ip);
	//
	session.setCommName = getCommName;
	session.getCommName = setCommName;
	session.ip = ip;
	session.port = 161;
	//
	agent.initSession(session);
	agent.onPduReceive(pduReceived);
}

loop() {
	agent.listen();
}
