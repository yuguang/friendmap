// Default empty project template
import bb.cascades 1.0


Page {
    content: Container {
        background: Color.create(0.25, 0.25, 0.25)
        attachedObjects: [
            Sheet {
                id: mySheet
                Page {
                    Container {
                        Label {
                            id: label1
                            text: "Title: "
                            multiline: true
                        }
                        Label {
                            id: label2
                            text: "Url: "
                            multiline: true
                        }
                        Button {
                            text: "Close"
                            onClicked: {
                                mySheet.close();
                            }
                        }
                    }
                }
            }
        ]
        Container {
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight
            }
            TextField {
                id: field1
            }
            Button {
                text: "Find"
                onClicked: {
                    myWebView.findText(field1.text);
                }
            }
        }
        Container {
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight
            }
            Button {
                text: "Forward"
                onClicked: {
                    myWebView.goForward();
                    myWebView.postMessage("Hi Javascript1");
                }
            }
            Button {
                text: "Refresh"
                onClicked: {
                    myWebView.reload();
                }
            }
            Button {
                text: "?"
                maxWidth: 200.0
                onClicked: {
                    mySheet.open();
                }
            }
        }   
        ScrollView {
            id: myScrollView
            scrollViewProperties.pinchToZoomEnabled: true
            scrollViewProperties.scrollMode: ScrollMode.Both
        
            WebView {
                id: myWebView
                url: "local:///assets/client/index.html"

                onLoadProgressChanged: {
                    progressIndicator.value = loadProgress / 100.0
                }
                onLoadingChanged: {
                    if (loadRequest.status == WebLoadStatus.Started) {
                        progressIndicator.opacity = 1.0
                    } else if (loadRequest.status == WebLoadStatus.Succeeded) {
                        progressIndicator.opacity = 0.0
                        //label1.text = "Title: " + myWebView.title;
                        //label2.text = "Url: " + myWebView.url;
                    } else if (loadRequest.status == WebLoadStatus.Failed) {
                        html = "<html><head><title>Fallback HTML on Loading Failed</title></head></html>"
                        progressIndicator.opacity = 0.0
                    }
                }
                onMinContentScaleChanged: {
                    myScrollView.scrollViewProperties.minContentScale = minContentScale;
                }
                onMaxContentScaleChanged: {
                    myScrollView.scrollViewProperties.maxContentScale = maxContentScale;
                }
                onMessageReceived: {
                    label1.text = "Title : " + message.origin;
                    label2.text = "Data: " + message.data;
                }
            }
        }
        Container {
            bottomPadding: 25
            horizontalAlignment: HorizontalAlignment.Center
            verticalAlignment: VerticalAlignment.Bottom
            ProgressIndicator {
                id: progressIndicator
                opacity: 0
            }
        }
    }
}
