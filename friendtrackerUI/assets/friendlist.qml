import bb.cascades 1.0

/**
 * ListView for display friends list
 * 
 * by Sukwon Oh
 */

Page {
    titleBar: TitleBar {
        title: "Friends"
    }
    
    actions: [
        InvokeActionItem {
            title: "Start a chat"
            imageSource: "asset:///images/chat.png"
            query {
                mimeType: "text/plain"
                invokeTargetId: "sys.bbm.sharehandler"
                invokeActionId: "bb.action.SHARE"
                data: ""
            }
        },
        InvokeActionItem {
            id: facebookShare
            title: "Share on facebook"
            imageSource: "asset:///images/facebook.png"
            query {
                mimeType: "text/plain"
                invokeTargetId: "Facebook"
                invokeActionId: "bb.action.SHARE"
                data: "@" + pinContainer.fakeBubble.bubbleText
            }
        }
    ]
    
    Container {
        ListView {
            dataModel: _friendtracker.friendListModel

            listItemComponents: [
                ListItemComponent {
                    type: "listItem"

                    StandardListItem {
                        id: friendItem
                        title: ListItemData.displayName
                        description: ListItemData.personalMessage
                        status: ListItemData.statusMessage
                        image: ListItemData.profilePicture
                        
                        contextActions: [
                            ActionSet {
                                title: "Show/Hide Friends"
                                ActionItem {
                                    title: friendItem.ListItem.view.getTitle(ListItemData.ppId, ListItemData.displayName)
                                    imageSource: friendItem.ListItem.view.getShowHideImage(ListItemData.ppId)
                                    enabled: friendItem.ListItem.view.shouldEnable(ListItemData.ppId)
                                    onTriggered: {
                                        var ppId = ListItemData.ppId;
                                        friendItem.ListItem.view.showHidePin(ppId);
                                    }
                                }
                            }
                        ]
                    } // StandardListItem
                } // ListItemComponent
            ] // listItemComponents
            
            function shouldEnable(ppId) {
                var marker = _mapView.getPin(ppId);
                if (marker != null) {
                    return true
                }
                return false;
            }
            
            function getTitle(ppId, displayName) {
                var marker = _mapView.getPin(ppId);
                if (marker != null) {
                    if (marker.visible) {
                        return "Hide " + displayName;
                    } else {
                        return "Show " + displayName;
                    }
                }
                return "";
            }
            
            function getShowHideImage(ppId) {
                var marker = _mapView.getPin(ppId);
                if (marker != null) {
                    if (marker.visible) {
                        return "asset:///images/hide.png";
                    } else {
                        return "asset:///images/show.png";
                    }
                }
                return "asset:///images/hide.png";
            }

            function showHidePin(ppId) {
                var marker = _mapView.getPin(ppId);
                if (marker != null) {
                    if (marker.visible) {
                        marker.visible = false;
                    } else {
                        marker.visible = true;
                    }
                }
                //navigationPane.pop();
            }

            /*
             * Center the map to the friend
             */
            onTriggered: {
                var selectedItem = dataModel.data(indexPath);
                var marker = _mapView.getPin(selectedItem.ppId);
                if (marker != null) {
                    mapview.latitude = marker.lat;
                    mapview.longitude = marker.lon;
                }
                navigationPane.pop();
            }

            // Override the itemType() function to return the proper type
            // for each item in the list. Because a GroupDataModel has only
            // two levels, use the index path to determine whether the item
            // is a header item or a list item.
            function itemType(data, indexPath) {
                if (indexPath.length == 1) {
                    // If the index path contains a single integer, the item
                    // is a "header" type item
                    return "header";
                } else {
                    // If the index path contains more than one integer, the
                    // item is a "listItem" type item
                    return "listItem";
                }
            }
        }
    }
}
