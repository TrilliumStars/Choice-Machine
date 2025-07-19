class story {//The fundamental of this project; stores information.
    constructor(name) {
        this.id = name;//a string to identify the story. No two stories should have the same id.
        this.elim = [];//a list of stories that this story has eliminated. 
        this.elimid = "";//the id of the story that eliminated this one
    }
    eliminate(q) {
        this.elim.push(q);
    }
}

function indexOfById(array, target) {//A modification of indexOf which finds based on the id element of the story
    return array.findIndex(item => item.id.toLowerCase() === target.id.toLowerCase());
}

//set up all of our stories
let Ns = [];
let eliminated = [];
let winners = [];
let UNDO = [];
const princess = [
    "Adversary", "Tower", "Nightmare", "Spectre", "Stranger", "Razor", "Witch", "Beast", "Prisoner", "Damsel", "Eye of the Needle",
    "Fury", "Apotheosis", "Moment of Clarity", "Wraith", "Dragon", "Thorn", "Wild", "Den", "Cage", "Burned Grey",
    "Drowned Grey", "Happily Ever After", "The Shifting Mound", "Base Princess"
];
const voice = [
    "Stubborn","Broken","Paranoid","Cold","Contrarian","Cheated","Opportunist","Hunted","Skeptic","Smitten","Hero"

]
const ending = [
    "Fight forever with Adversary", "Bow down before the tower", "Free the Nightmare", "Free the Spectre", "Stranger", "Fall down the stairs with the Witch",
    "Locked in the basement by the Witch", "Free the Beast", "Free the Prisoner by waiting", "Free the Prisoner's head",
    "Free the Damsel", "Deconstruct the Damsel", "With Hunted, slay the Eye of the Needle", "Free the Eye of the Needle", "Die at the doormat by the Needle",
    "Fight the Needle Head-on downstairs", "Free the Fury", "Endure her torture, then slay the Fury", "Endure her torture, then leave the Fury, alone",
    "Slay the Tower, then Slay the Fury", "You didn't hear no bell, and Slayed the Fury", "Unravel the Fury into ribbons", "With Contrarian, scar the apotheosis",
    "With Paranoid, unravel the apotheosis", "Chain yourself to the Apotheosis", "Free the Apotheosis", "Free the Moment of Clarity", "Free the Wraith",
    "Fall forever with the wraith", "Become one with the Dragon", "Free the Dragon", "Leave the Gentle Dragon in the Basement", "Empty your mind, and Slay the Razor using your blade",
    "Be shapeless, and let the Razor slay herself", "Free the Thorn", "Attempt to Slay the Thorn", "Attempt to leave the Thorn", "With the Wild, break your cage",
    "Free the wounded wild", "Slay the wounded Wild", "Embrace instinct with the Den", "With stubborn, retain your humanity and Slay the Den",
    "Disobey the voices in your head in the Den", "Lure the Den out, then slay her", "Lure the Den out, then flinch", "Lure the Den out, then starve to death", "Free the Den",
    "With Paranoid, slay the cage", "Lose your head with the Cage", "Free the Cage", "Tease the cage with freedom, then drop her", "Slay the Damsel, then burn with her",
    "Slay the Prisoner, then Drown with her","Free the Happily Ever After","Slay the Happily Ever After","Sit forever with the Happily Ever After"
]
const ending2 = [
    "The Good ending", "Oblivion", "Your new World", "A new and unending Dawn", "There are no endings",
    "Reset the Construct","The Unknown Together"
]
lists = [princess, voice, ending,ending2];
let DTA = princess;
const tooltip = document.createElement("div");
first_setup();
function hide_setup_buttons() {//hide the buttons which call setup()
    document.getElementById("princesses").style.display = "none";//make sure all buttons are okay.
    document.getElementById("voices").style.display = "none";
    document.getElementById("endings").style.display = "none";
    document.getElementById("endings2").style.display = "none";
}
function show_setup_buttons() {//show the buttons which call setup()
    document.getElementById("princesses").style.display = "inline-block";
    document.getElementById("voices").style.display = "inline-block";
    document.getElementById("endings").style.display = "inline-block";
    document.getElementById("endings2").style.display = "inline-block";
}

function setup(mode) {//A function which prepares the game to be played. Triggered by three buttons.
    console.log(mode);
    document.getElementById("listMessage").innerText = "Progress and Rankings (Hover to show more info)";
    document.getElementById("theGrid").style.display = "inline-grid";
    Ns = [];//empty all of the lists
    eliminated = [];
    winners = [];
    UNDO = [];
    DTA = lists[mode];
    console.log(DTA);
    for (let i = 0; i < DTA.length; i++) {
        Ns.push(new story(DTA[i]));//fill Ns
    }
    hide_setup_buttons();
    document.getElementById("choice1").style.display = "inline-block";
    document.getElementById("choice2").style.display = "inline-block";
    document.getElementById("undoBtn").style.display = "inline-block"; 
    document.getElementById("skipBtn").style.display = "inline-block";
    document.getElementById("resetBtn").style.display = "inline-block";
    document.getElementById("saveBtn").style.display = "inline-block";
    document.getElementById("rescueBtn").style.display = "inline-block";
    //document.getElementById("list1").style.display = "inline-block";
    renderAllLists();
    updateChoiceButtons();
    console.log("Success!");

}
function game() {//a modified reset() function which should return the game to its original state
    if (confirm("Are you Sure you would like to reset your entire list?")) {
        show_setup_buttons();
        Ns = [];
        eliminated = [];
        winners = [];
        UNDO = [];
        document.getElementById("resetBtn").style.display = "none";
        document.getElementById("saveBtn").style.display = "none";
        document.getElementById("rescueBtn").style.display = "none";
        document.getElementById("undoBtn").style.display = "none";
        document.getElementById("skipBtn").style.display = "none";
        document.getElementById("choice1").style.display = "none";
        document.getElementById("choice2").style.display = "none";
        document.getElementById("endMessage").innerText = "";
        document.getElementById("duringMessage").innerText = "Choose 1 to rank:";
        document.detElementById("errorMessage").innerText = "";
        document.getElementById("successMessage").innerText = "";
        renderAllLists();
    }
    
}

function showTooltip(target, text) {//manage the tooltip
    tooltip.innerText = text;
    tooltip.style.display = "block";

    const rect = target.getBoundingClientRect();
    tooltip.style.left = `${rect.right + 5 + scrollX}px`;
    tooltip.style.top = `${rect.top + scrollY}px`;
}

function hideTooltip() {
    tooltip.style.display = "none";
}

function renderList(list, elementId) {//manages the visuals
    const container = document.getElementById(elementId);
    container.innerHTML = ""; //Clear previous content

    list.forEach(obj => {
        const div = document.createElement("div");
        div.className = "object";
        if (elementId === "list3") {//special display for winners
            div.innerText = (indexOfById(winners,obj) + 1) + ") " + obj.id;
        }
        else {
            div.innerText = obj.id;
        }
        div.style = "background-color: #999999;";
        if (elementId === "list2") {//tooltip for eliminated
            
            div.addEventListener("mouseenter", () => {
                showTooltip(div, "Eliminated by " + obj.elimid);
            });
            div.addEventListener("mouseleave", hideTooltip);
        }
        if (elementId === "list1") {//tooltip for choosing
            
            div.addEventListener("mouseenter", () => {
                let rab = "eliminating: ";
                if (obj.elim == []) {
                    rab = "eliminating nothing";
                }
                else {
                    for (let i = 0; i < obj.elim.length; i++) {
                        rab = rab + obj.elim[i].id + ", ";

                    }
                }
                showTooltip(div, rab);
            });
            div.addEventListener("mouseleave", hideTooltip);
        }

        container.appendChild(div);
    });
}

function renderAllLists() {
    renderList(Ns, "list1");
    renderList(eliminated, "list2");
    renderList(winners, "list3");
    //renderList(UNDO, "list4");
}

let currentChoices = [null, null, null];//two stories to choose from, plus a control element to prevent the same story twice in a row if possible
function getrandlists() {//prepares two unique stories. Optionally 
    if (Ns.length < 2) return [null,null,null];
    if (Ns.length == 2) {//only two options
        return [Ns[0], Ns[1], null];
    }
    if (currentChoices[2] == null) {//the program doesn't remember what happened last round
        let index = Math.floor(Math.random() * Ns.length);
        let index2 = index;
        while (index2 == index) {
            index = Math.floor(Math.random() * Ns.length);
        }
        return [Ns[index], Ns[index2], null];
    }
    else {//the program does remember what happened last round
        let index = Math.floor(Math.random() * Ns.length);
        let index2 = index;
        while (Ns[index].id === currentChoices[2].id) {
            index = Math.floor(Math.random() * Ns.length);
        }
        while (Ns[index2].id === currentChoices[2].id || index === index2) {
            index2 = Math.floor(Math.random() * Ns.length);
        }
        return [Ns[index], Ns[index2], null];
    }
}
function estimate(val) {//estimate how many choices remain based on the size of the data set.
    if (val < 32) {
        return Math.floor(1.245 * ((val - 1) ** 1.253));
    }
    return Math.floor(1.694 * ((val - 1) ** 1.165));
    //the number of choices left should be:
    //num = estimate(Ns.length + eliminated.length) - eliminated.length';

}
function updateChoiceButtons() {//update the buttons and clear any old messages
    
    if (Ns.length < 2) {//kill the process once only two choices remain
        document.getElementById("choice1").style.display = "none";
        document.getElementById("choice2").style.display = "none";
        document.getElementById("undoBtn").style.display = "none"; 
        document.getElementById("skipBtn").style.display = "none";
        document.getElementById("rescueBtn").style.display = "none";
        hideBtn();
        document.getElementById("resetBtn").innerText = "Reset";

        const header = document.getElementById("endMessage");
        header.innerText = "Congratulations! You've chosen all of your favorites!";
        document.getElementById("successMessage").innerText = "";
        document.getElementById("duringMessage").innerText = "";
        document.getElementById("Estimation").innerText = "";
        document.getElementById("listMessage").innerText = "";
        return;
    }
    currentChoices = getrandlists();//get the buttons
    const header = document.getElementById("duringMessage");
    header.innerText = "Click your favorite out of these 2:";
    document.getElementById("successMessage").innerText = "";
    document.getElementById("Estimation").innerText = "Approximately " + (estimate(Ns.length + eliminated.length) - eliminated.length) + " choices left";
    document.getElementById("skipBtn").innerText = "Skip";
    document.getElementById("choice1").innerText = currentChoices[0] ? currentChoices[0].id : "N/A";
    document.getElementById("choice2").innerText = currentChoices[1] ? currentChoices[1].id : "N/A";
}
function handleChoice(index) {
    let selectedStory = currentChoices[1 - index];
    if (!selectedStory) {
        return;
    }
    winstory = Ns[indexOfById(Ns,currentChoices[index])];
    selectedStory.elimid = winstory.id;
    currentChoices[2] = winstory;
    let lose = indexOfById(Ns,currentChoices[1 - index]);
    winstory.eliminate(selectedStory);
    eliminated.push(selectedStory);
    Ns.splice(lose, 1);
    let u = indexOfById(UNDO,selectedStory);
    while (u !== -1) {
        UNDO.splice(u, 1);
        u = indexOfById(UNDO,selectedStory);
    }
    UNDO.push(selectedStory);
    let i = 0;
    while (Ns.length === 1) {
        currentChoices = [null, null,null];
        i++
        winstory = Ns.pop();
        //winstory.id = (list3.length + 1) + ") " + winstory.id;
        winners.push(winstory);
        //list3[list3.length - 1].id = list3.length + " " + list3[list3.length - 1].id;
        console.log(winstory.elim.length);
        for (let i = 0; i < winstory.elim.length; i++) {
            const beta = winstory.elim[i];
            console.log(winstory.elim[i].id);
            console.log(indexOfById(eliminated, beta));
            eliminated.splice(indexOfById(eliminated, beta), 1);
            UNDO.splice(indexOfById(UNDO, beta), 1);
            Ns.push(beta);
        }
        winstory.elim = [];
        u = indexOfById(UNDO,winstory);
        while (u !== -1) {
            UNDO.splice(u, 1);
            u = indexOfById(UNDO,winstory);
        }
        UNDO.push(winstory);
        
        
    }
    renderAllLists();


    // Placeholder: Your real logic goes here
    console.log("You selected:", selectedStory.id);
    //dummyAction(selectedStory);

    // Pick two new random choices
    document.getElementById("errorMessage").innerText = "";
    updateChoiceButtons();
}
function handleUndo() {
    if (UNDO.length === 0) {
        document.getElementById("errorMessage").innerText = "You can't undo any more";
        document.getElementById("successMessage").innerText = "";
        return;
    }
    let yggdrasil = UNDO.pop();
    
    let loc = indexOfById(eliminated,yggdrasil);
    if (loc === -1) {
        loc = indexOfById(winners, yggdrasil);
        yggdrasil = winners[loc];
        winners.splice(loc, 1);
        yggdrasil.elim = [];
        yggdrasil.elimid = "";
        Ns.push(yggdrasil);
        document.getElementById("successMessage").innerText = "Returned " + yggdrasil.id + " from the ranked list";
    }
    else {
        yggdrasil = eliminated[loc];
        eliminated.splice(loc, 1);
        dummyStory = new story(yggdrasil.elimid);
        let pos = indexOfById(eliminated, dummyStory);
        let ElimBy;
        if (pos === -1) {
            pos = indexOfById(Ns, dummyStory);
            ElimBy = Ns[pos];
        }
        else {
            ElimBy = eliminated[pos];
        }
        ElimBy.elim.splice(indexOfById(ElimBy.elim, yggdrasil), 1);
        yggdrasil.elimid = "";
        Ns.push(yggdrasil);
        document.getElementById("successMessage").innerText = "Returned "+ yggdrasil.id + " from eliminated";
    }
    document.getElementById("Estimation").innerText = "Approximately " + (estimate(Ns.length + eliminated.length) - eliminated.length) + " choices left";
    //if(Ns.length + eliminated.length + list3)
    renderAllLists();

    //document.getElementById("errorMessage").innerText = "You can't undo any more";
}
function ShowRescue() {
    document.getElementById("errorMessage").innerText = "";
    document.getElementById("userInput2").style.display = "inline-block";
    document.getElementById("userInputBtn2").style.display = "inline-block";
    document.getElementById("cancelBtn").style.display = "inline-block";
    return;
}
function rescue() {
    let input = document.getElementById("userInput2").value;
    hideBtn();
    let dummyStory = new story(input);
    let u = indexOfById(eliminated, dummyStory);
    if (u === -1) {
        let u = indexOfById(winners, dummyStory);
        if (u === -1) {
            let u = indexOfById(Ns, dummyStory);
            if (u === -1) {
                document.getElementById("errorMessage").innerText = "Can't find item called \"" + input + "\". Did you mispell it?";
                return;
            }
            document.getElementById("errorMessage").innerText = ("\"" + input + "\" Doesn't need to be rescued.")
            return;
        }
        if (confirm(input + " has already been ranked. Would you like to move it back to the choosing list?")) {
            dummyStory = winners[u];
            winners.splice(u, 1);
            Ns.push(dummyStory);
        }
        renderAllLists();
        updateChoiceButtons();
        return;
    }
    dummyStory = eliminated[u];
    if (confirm(input + " was eliminated by " + dummyStory.elimid + ". Would you like to rescue it?")) {
        eliminated.splice(u, 1);
        Ns.push(dummyStory);
    }
    renderAllLists();
    updateChoiceButtons();
    document.getElementById("successMessage").innerText = "Succesfully returned "+ input + "To the choosing list";
    return;
}
function OpenImport() {
    document.getElementById("successMessage").innerText = "";
    document.getElementById("errorMessage").innerText = "";
    document.getElementById("userInput").style.display = "inline-block";
    document.getElementById("userInputBtn").style.display = "inline-block";
    document.getElementById("cancelBtn").style.display = "inline-block";
    return;
}
function hideBtn() {
    document.getElementById("userInput").style.display = "none";
    document.getElementById("userInputBtn").style.display = "none";
    document.getElementById("userInput2").style.display = "none";
    document.getElementById("userInputBtn2").style.display = "none";
    document.getElementById("cancelBtn").style.display = "none";
}
function Import(){
    let input = document.getElementById("userInput").value;
    hideBtn()
    document.getElementById("errorMessage").innerText = "";
    numers = input.charCodeAt(0) - 33;
    setup(numers);
    numers = lists[numers].length;
    //console.log(input[0]);
    if (input.length === 1) {
        Ns = [];
        eliminated = [];
        winners = [];
        UNDO = [];
        for (let i = 0; i < DTA.length; i++) {
            Ns.push(new story(DTA[i]));
        }
        document.getElementById("choice1").style.display = "inline-block";
        document.getElementById("choice2").style.display = "inline-block";
        document.getElementById("undoBtn").style.display = "inline-block";
        document.getElementById("skipBtn").style.display = "inline-block";
        document.getElementById("endMessage").innerText = "";
        updateChoiceButtons();
        renderAllLists();
        document.getElementById("successMessage").innerText = "Succesfully Imported Save Code";
        return;
    }
    input = input.slice(1);
    places = input.slice(0, Math.ceil(numers * Math.log(3) / Math.log(94)));
    console.log(places);
    input = input.slice(Math.ceil(numers * Math.log(3) / Math.log(94)));
    places = string_to_list(places, 3n);
    while (places.length < numers) {
        places.push(0);
    }
    if (places.length !== numers) {
        /*console.log(places);
        console.log(numers);*/
        document.getElementById("errorMessage").innerText = "Critical Error, save code is bad. Error code 1";
        return;
    }
    lengths = [0,0,0];
    for (let i = 0; i < places.length; i++) {
        lengths[places[i]]++;
    }
    if (lengths[0] + lengths[1] + lengths[2] !== numers) {
        document.getElementById("errorMessage").innerText = "Critical Error, save code is bad. Error code 2";
        return;
    }
    elims = input.slice(0, Math.ceil(lengths[1] * Math.log(numers) / Math.log(94)));
    //console.log(elims);
    elims = string_to_list(elims, BigInt(numers));
    while (elims.length < lengths[1]) {
        elims.push(0);
    }
    if (elims.length !== lengths[1]) {
        //console.log(elims);
        //console.log(lengths);
        document.getElementById("errorMessage").innerText = "Critical Error, save code is bad. Error code 3";
        return;
    }
    input = input.slice(Math.ceil(lengths[1] * Math.log(numers) / Math.log(94)));
    //console.log(input);
    let wins = string_to_list(input, BigInt(lengths[2]));
    /*console.log(numers);
    console.log(places);
    console.log(elims);
    console.log(wins);*/
    while (wins.length < lengths[2]) {
        wins.push(0);
    }
    if (wins.length !== lengths[2]) {
        document.getElementById("errorMessage").innerText = "Critical Error, save code is bad. Error code 4";
        return;
    }
    let elim_index = 0;
    let win_index = 0;
    Ns = [];
    eliminated = [];
    winners = [];
    UNDO = [];
    for (let i = 0; i < numers; i++) {
        if (places[i] === 0) {
            Ns.push(new story(DTA[i]));
        }
        if (places[i] === 1) {
            eliminated.push(new story(DTA[i]));
        }
        if (places[i] === 2) {
            winners.push(new story(DTA[i]));
        }
    }
    let dummyStory = new story("");;
    let loc;
    for (let e = 0; e < elims.length; e++) {
        dummyStory.id = DTA[elims[e]];
        let badstory;
        loc = indexOfById(Ns, dummyStory);
        if (loc === -1) {
            loc = indexOfById(eliminated, dummyStory);
            badstory = eliminated[loc];
        }
        else {
            badstory = Ns[loc];
        }
        eliminated[e].elimid = badstory.id;
        badstory.elim.push(eliminated[e]);
    }
    rwins = [];
    for (let w = 0; w < wins.length; w++) {
        rwins.push(dummyStory);
    }
    for (let w = 0; w < wins.length; w++) {
        rwins[wins[w]] = winners[w]; 
    }
    winners = rwins;
    document.getElementById("choice1").style.display = "inline-block";
    document.getElementById("choice2").style.display = "inline-block";
    document.getElementById("undoBtn").style.display = "inline-block"; 
    document.getElementById("skipBtn").style.display = "inline-block";
    document.getElementById("endMessage").innerText = "";
    document.getElementById("princesses").style.display = "none";
    document.getElementById("voices").style.display = "none";
    document.getElementById("endings").style.display = "none";
    updateChoiceButtons();
    document.getElementById("successMessage").innerText = "Succesfully Imported Save Code";
    renderAllLists();
    return;

}
function Export(){
    let data = 0n;
    let debug;
    let places = [];
    let OPT = "";
    let dummyStory = new story("");

    code1 = lists.findIndex(item => item.indexOf((Ns.length !== 0 ? Ns[0].id : winners[0].id)) !== -1);
    console.log(code1);
    for (let i = 0; i < DTA.length; i++) {
        dummyStory.id = (DTA[i]);
        let y = 0n;
        if (indexOfById(eliminated, dummyStory) !== -1) {
            y = 1n;
        }
        else {
            if (indexOfById(winners, dummyStory) !== -1) {
                y = 2n;
            }
        }
        places.push(y);
    }
    //OPT = String.fromCharCode(33 + Ns.length + eliminated.length + winners.length);
    OPT = String.fromCharCode(33 + code1);
    console.log(places);
    let str = list_to_string(places, 3n);
    console.log(string_to_list(str, 3n));
    let lgth = Math.ceil(places.length * Math.log(3) / Math.log(94));
    while (str.length % lgth) {
        str += "!";
    }
    OPT += str;
    debug = string_to_list(str, 3n);
    for (let i = 0; i < debug.length; i++) {
        if (places[i] !== BigInt(debug[i])) {
            document.getElementById("errorMessage").innerText = "Critical Error, unable to save. Error code 1";
            return;
        }
    }
    elims = [];
    //console.log(DTA.length);
    for (let i = 0; i < DTA.length; i++) {
        if (places[i] !== 1n) {
            continue;
        }
        dummyStory.id = DTA[i];
        elims.push(BigInt(DTA.indexOf(eliminated[indexOfById(eliminated, dummyStory)].elimid)));
        /*console.log(places[i]);
        console.log(DTA[i]);
        console.log(indexOfById(eliminated, dummyStory));
        console.log((indexOfById(eliminated, dummyStory).elimid));
        console.log(DTA.indexOf(indexOfById(eliminated, dummyStory).elimid));*/
    }
    console.log(elims);
    str = list_to_string(elims, BigInt(DTA.length));
    lgth = Math.ceil(elims.length * Math.log(DTA.length) / Math.log(94));
    while (str.length % lgth) {
        str += "!";
    }
    console.log(string_to_list(str, BigInt(DTA.length)));
    debug = string_to_list(str, BigInt(DTA.length));
    for (let i = 0; i < debug.length; i++) {
        if (elims[i] !== BigInt(debug[i])) {
            document.getElementById("errorMessage").innerText = "Critical Error, unable to save. Error code 2";
            return;
        }
    }
    OPT += str;
    elims = [];
    for (let i = 0; i < DTA.length; i++) {
        if (places[i] !== 2n) {
            continue;
        }
        dummyStory.id = DTA[i];
        elims.push(BigInt(indexOfById(winners, dummyStory)));
    }
    console.log(elims);
    str = list_to_string(elims, BigInt(winners.length));
    lgth = Math.ceil(elims.length * Math.log(winners.length) / Math.log(94));
    while (str.length % lgth) {
        str += "!";
    }
    console.log(string_to_list(str, BigInt(winners.length)));
    debug = string_to_list(str, BigInt(winners.length));
    for (let i = 0; i < debug.length; i++) {
        if (elims[i] !== BigInt(debug[i])) {
            document.getElementById("errorMessage").innerText = "Critical Error, unable to save. Error code 3";
            return;
        }
    }
    OPT += str;
    document.getElementById("Estimation").innerText = "Save code:    " + OPT;
    navigator.clipboard.writeText(OPT);
    alert("Here's a save code: \n\n" + OPT + "\n\nIt's been copied to your clipboard for convenience.");
}
function list_to_string(lst, base) {
    let y = list_to_int(lst, base);
    return (int_to_string(y));
}
function list_to_int(Lst, base) {
    let data = 0n
    let mult = 1n;
    for (let i = 0; i < Lst.length; i++) {

        data += Lst[i] * mult;
        mult *= BigInt(base);
    }
    return data;
}
function int_to_string(data) {
    //console.log("checkpoint 1");
    chars = [];
    while (data !== 0n) {
        chars.push(Number(data % 94n));
        data -= data % 94n;
        data /= 94n;
        //console.log(data);
    }
    let ret = "";
    for (let i = 0; i < chars.length; i++) {
        ret += String.fromCharCode(33 + chars[i]);
    }
    return ret;
}
function string_to_int(data) {
    let yodel = 1n;
    let datata = 0n;
    for (let i = 0; i < data.length; i++) {
        //console.log(typeof (datata));
        //console.log(typeof ((data.charCodeAt(i) - 33)));
        //console.log(typeof (yodel));
        datata += BigInt(data.charCodeAt(i) - 33) * yodel;
        yodel *= 94n;
    }
    return datata;
}
function int_to_list(data, base) {
    lst = [];
    while (data !== 0n) {
        lst.push(Number(data % base));
        data -= data % base;
        data /= base;
        //console.log(data);
    }
    return lst;
}
function string_to_list(data, base) {
    return (int_to_list(string_to_int(data), base));
}
function first_setup() {
    //game();
    // Render one list into its column
    // Create and style tooltip element
    
    tooltip.style.position = "absolute";
    tooltip.style.padding = "6px 10px";
    tooltip.style.background = "#333";
    tooltip.style.color = "#fff";
    tooltip.style.borderRadius = "6px";
    tooltip.style.fontSize = "14px";
    tooltip.style.pointerEvents = "none";
    tooltip.style.display = "none";
    document.body.appendChild(tooltip);
    //document.getElementById("list1").style.display = "none";
    hideBtn();
    document.getElementById("choice1").style.display = "none";
    document.getElementById("choice2").style.display = "none";
    document.getElementById("undoBtn").style.display = "none";
    document.getElementById("skipBtn").style.display = "none";
    document.getElementById("resetBtn").style.display = "none";
    document.getElementById("saveBtn").style.display = "none";
    document.getElementById("rescueBtn").style.display = "none";
    document.getElementById("cancelBtn").style.display = "none";
    document.getElementById("listMessage").innerText = "";
    document.getElementById("duringMessage").innerText = "Choose 1 to rank:";
    document.getElementById("theGrid").style.display = "none";
    
}
