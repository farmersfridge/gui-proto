import QtQuick 2.5
import ".."

Command {
    id: checkOutCommand

    // Execute:
    function execute()
    {
        mainApplication.showPopup("_checkoutpopup_")
    }
}
