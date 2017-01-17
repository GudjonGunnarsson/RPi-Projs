const Discord = require('discord.js');
const bot = new Discord.Client();
const token = '<snip>';
var schedule = require('node-schedule');

bot.on('ready', () => {
  console.log('Running!');

  var rule = new schedule.RecurrenceRule();
  rule.minute = 30; rule.hour = 17; rule.dayOfWeek =[1, 3, 6];

  var j = schedule.scheduleJob(rule, function(){
    bot.channels.get("<snip>").sendMessage("Reminder: ");
  });

});

bot.on("message", msg => {
  let prefix = "!";
  var role = msg.guild.roles.find("name", "Raider");

  if (msg.author.bot && msg.content.startsWith("Reminder:")){
    bot.channels.get("<snip>").sendMessage(role + " - Dont forget to sign for the raids. Groups are set roughly one hour before the raid starts.");
    bot.channels.get("<snip>").sendMessage("If you set tentative, send a message to an officer!");
  }

  if (!msg.content.startsWith(prefix)) return;
  if (msg.author.bot) return;

  if (msg.content.startsWith(prefix + "tomes")) {
    let voca = msg.guild.members.get("<snip>");
    msg.channel.sendMessage('Ask ' + voca + ' for tomes!');
  }

  if (msg.content.startsWith(prefix + "info")) {
    msg.channel.sendMessage('Commands: !scrubnub <@someone>, !tomes, !uptime, !help/info');
  }
  if (msg.content.startsWith(prefix + "help")) {
    msg.channel.sendMessage('Commands: !scrubnub <@someone>, !tomes, !uptime, !help/info');
  }

  if (msg.content.startsWith(prefix + "uptime")){
    msg.channel.sendMessage('Bot initiated at ' + bot.readyAt + ' and the uptime is ' + bot.uptime);
  }

  if (msg.content.startsWith(prefix + "version") || msg.content.startsWith(prefix + "v")){
    msg.channel.sendMessage('Version 1');
  }

  if (msg.content.startsWith(prefix + "scrubnub")) {
    let user = msg.mentions.users.first();
    msg.channel.sendMessage(user + ' is a skkkrrruubbb');
  }
});

bot.on('error', e => { console.error(e); });

bot.login(token);