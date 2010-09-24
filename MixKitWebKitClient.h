#ifndef MOTIONBOX_MIXKIT_WEBKIT_CLIENT_H_
#define MOTIONBOX_MIXKIT_WEBKIT_CLIENT_H_

#include <webkit/glue/simple_webmimeregistry_impl.h>
#include <webkit/glue/webfileutilities_impl.h>
#include <webkit/glue/webclipboard_impl.h>
#include <webkit/glue/webkitclient_impl.h>

class MixKitWebKitClient : public webkit_glue::WebKitClientImpl {
public:
    MixKitWebKitClient() {};
    virtual ~MixKitWebKitClient() {};

    virtual WebKit::WebMimeRegistry* mimeRegistry() { return &mimeRegistryImpl; }
    virtual WebKit::WebClipboard* clipboard() { return &clipboardImpl; }
    virtual WebKit::WebFileUtilities* fileUtilities() { return &fileUtiliesImpl; }
    
    //XXX this is required
    //virtual WebKit::WebBlobRegistry* blobRegistry() 
    //virtual WebFileSystem* fileSystem()


private:
    webkit_glue::SimpleWebMimeRegistryImpl mimeRegistryImpl;
    webkit_glue::WebClipboardImpl clipboardImpl;
    webkit_glue::WebFileUtilitiesImpl fileUtiliesImpl;
    //XXXscoped_refptr<TestShellWebBlobRegistryImpl> blob_registry_;
};

#endif