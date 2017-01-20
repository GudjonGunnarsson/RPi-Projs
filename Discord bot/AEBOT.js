const Discord = require('discord.js');
const bot = new Discord.Client();
const token = '<snip>';
var schedule = require('node-schedule');

bot.on('ready', () => {
  console.log('Running!');
  bot.user.setGame("Sikk Meme m8");

  var rule = new schedule.RecurrenceRule();
  rule.minute = 30;
  rule.hour = 16;
  rule.dayOfWeek =[1, 3, 6];

  var j = schedule.scheduleJob(rule, function(){
    bot.channels.get("<snip>").sendMessage("wKdW74");
  });
});

bot.on("message", msg => {
  let prefix = "!";
  let role = msg.guild.roles.find("name", "HNIC");
  var mini = bot.users.get("<snip>");

  if (msg.author.bot && msg.content.startsWith("wKdW74")) {
    var msgArray = [];
    msgArray.push("@role" + " - Dont forget to sign for the raids.");
    msgArray.push("Groups are set roughly one hour before the raid starts.");
    msgArray.push("If you set tentative, send a message to an officer!");
    setTimeout(() => {
      msg.edit("Reminder: ");
      msg.channel.sendMessage(msgArray);
    }, 100);
  }
  if (!msg.content.startsWith(prefix)) return;
  if (msg.author.bot) return;

  Date.prototype.getWeek = function() {
    var onejan = new Date(this.getFullYear(), 0, 1);
    return Math.ceil((((this - onejan) / 86400000) + onejan.getDay() + 4) / 7);
  }

  if (msg.content.startsWith(prefix + "time")) {
    var now = new Date();
    msg.channel.sendMessage("Servertime: " + now);
  }
  if (msg.content.startsWith(prefix + "affixes")) {
    var weekNumber = (new Date()).getWeek();
    var affixArray1 = [4, 12, 20, 28, 36, 44, 52];
    var affixArray2 = [5, 13, 21, 29, 37, 45];
    var affixArray3 = [6, 14, 22, 30, 38, 46];
    var affixArray4 = [7, 15, 23, 31, 39, 47];
    var affixArray5 = [8, 16, 24, 32, 40, 48];
    var affixArray6 = [9, 17, 25, 33, 41, 49, 1];
    var affixArray7 = [10, 18, 26, 34, 42, 50, 2];
    var affixArray8 = [11, 19, 27, 35, 43, 51, 3];

    for (var i = 0; i < affixArray1.length; i++) {
      if(weekNumber == affixArray1[i]) {
        msg.channel.sendMessage("Current weeks affixes are: Raging, Necrotic & Fortified.");
        msg.channel.sendMessage("Next week: Bolstering, Overflowing & Tyrannical.");
    }}
    for (var i = 0; i < affixArray2.length; i++) {
      if(weekNumber == affixArray2[i]) {
        msg.channel.sendMessage("Current weeks affixes are: Bolstering, Overflowing & Tyrranical.");
        msg.channel.sendMessage("Next week: Sanguine, Volcanic & Fortified.");
    }}
    for (var i = 0; i < affixArray3.length; i++) {
      if(weekNumber == affixArray3[i]) {
        msg.channel.sendMessage("Current weeks affixes are: Sanguine, Volcanic & Fortified.");
        msg.channel.sendMessage("Next week: Teeming, Necrotic & Tyrannical.");
    }}
    for (var i = 0; i < affixArray4.length; i++) {
      if(weekNumber == affixArray4[i]) {
        msg.channel.sendMessage("Current weeks affixes are: Teeming, Necrotic & Tyrannical.");
        msg.channel.sendMessage("Next week: Raging, Volcanic & Tyrannical.");
    }}
    for (var i = 0; i < affixArray5.length; i++) {
      if(weekNumber == affixArray5[i]) {
        msg.channel.sendMessage("Current weeks affixes are: Raging, Volcanic & Tyrannical.");
        msg.channel.sendMessage("Next week: Bolstering, Skittish & Fortified.");
    }}
    for (var i = 0; i < affixArray6.length; i++) {
      if(weekNumber == affixArray6[i]) {
        msg.channel.sendMessage("Current weeks affixes are: Bolstering, Skittish & Fortified.");
        msg.channel.sendMessage("Next week: Sanguine, Overflowing & Tyrannical.");
    }}
    for (var i = 0; i < affixArray7.length; i++) {
      if(weekNumber == affixArray7[i]) {
        msg.channel.sendMessage("Current weeks affixes are: Sanguine, Overflowing & Tyrannical.");
        msg.channel.sendMessage("Next week: Teeming, Skittish & Fortified.");
    }}
    for (var i = 0; i < affixArray8.length; i++) {
      if(weekNumber == affixArray8[i]) {
        msg.channel.sendMessage("Current weeks affixes are: Teeming, Skittish & Fortified.");
        msg.channel.sendMessage("Next week: Raging, Necrotic & Fortified.");
    }}
  }

  if (msg.content.startsWith(prefix + "help") || msg.content.startsWith(prefix + "info")) {
    var msgArray = [];
    msgArray.push("Bot Commands:");
    msgArray.push("Command                Description");
    msgArray.push("!scrubnub <@someone>   Call someone a scrub.");
    msgArray.push("!affixes               Shows you M+ affixes for current & next week.");
    msgArray.push("!time                  What the servertime is currently.");
    msgArray.push("!initiated             When bot was started.");
    msgArray.push("!help/info             This message.");
    msg.channel.sendMessage(msgArray);
  }

  if (msg.content.startsWith(prefix + "test")) {
    var messagetest = "Hello"
    //msg.author.sendMessage(messagetest);
    //msg.sendMessage(mini, messagetest);
  }

  if (msg.content.startsWith(prefix + "initiated"))
    msg.channel.sendMessage("Bot initiated at " + bot.readyAt + "\nAnd the current uptime is " + (Math.round(bot.uptime / (1000 * 60 * 60))) + "hrs.");
  if (msg.content.startsWith(prefix + "version"))
    msg.channel.sendMessage("Version 2 - Affixes");
  if (msg.content.startsWith(prefix + "scrubnub")) {
    let user = msg.mentions.users.first();
    msg.channel.sendMessage(user + ' is a skkkrrruubbbnub');
  }
});

bot.on('error', e => { console.error(e); });

bot.login(token);