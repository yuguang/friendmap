import bb.cascades 1.0

Page {
    ScrollView {
        scrollViewProperties.pinchToZoomEnabled: true
        scrollViewProperties.scrollMode: ScrollMode.Both
        Container {
            background: Color.create ("#f8f8f8")
            layout: StackLayout {
                orientation: LayoutOrientation.TopToBottom
            }
            WebView {
                url: "http://sukwonoh.com"
            }
        }
    }
}
