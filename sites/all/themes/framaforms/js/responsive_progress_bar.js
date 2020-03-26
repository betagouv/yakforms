function responsive_progress_bar() {
    if(window.screen.width < 768 || window.screen.height < 1024) {
        var divnode = document.createElement("h5"); 
        // get current page number 
        var current_pos = document
        .querySelector(".webform-progressbar-page.current")
        .querySelector(".webform-progressbar-page-number")
        .innerText; 
        // get total number of titles 
        var total_number_of_titles = document
        .getElementsByClassName("webform-progressbar-page-number")
        .length;
        divnode.innerHTML = "Étape " + current_pos + " / " + total_number_of_titles + " - "
        + document.querySelector(".webform-progressbar-page.current")
        .querySelector(".webform-progressbar-page-label")
        .innerText ; 

        document.getElementById("page-title").appendChild(divnode); 
        document.querySelector(".webform-progressbar-outer").style.display="none"; 
    }
}

window.onload = responsive_progress_bar; 