let time_inputs = document.getElementsByClassName("time-set");

Array.from(time_inputs).forEach(input => {
    input.addEventListener("change", e => {
        console.log("validating value...");
        if (!validate_time_input(input)) {
            console.log("Verification of time value failed!");
            window.alert("Value exceeds valid range");
            input.value = null;
        }
    });
});

function validate_time_input(html_node) {
    val = html_node.value;
    if (html_node.name == "time-set-minutes" || html_node.name == "time-set-seconds") {
        if (val <= 0 || val > 60) {
            return false;
        }
    }

    if (html_node.name == "time-set-hours") {
        if(val <= 0 || val > 12) {
            return false;
        }
    }

    return true;
}
