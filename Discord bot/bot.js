const Discord = require('discord.js');
const bot = new Discord.Client();
const token = 'tokenhere';

bot.on('ready', () => {
  console.log('Running!');
});

bot.on("message", msg => {
  let prefix = "!";
  let role = msg.guild.roles.find("name", "HNIC");

  if (!msg.content.startsWith(prefix)) return;
  if (msg.author.bot) return;

  if (msg.content.startsWith(prefix + "test")) {
    msg.channel.sendMessage(role + ': message here');
    msg.channel.sendMessage("Posting this message once every 48hrs");
    setInterval(function(){
      msg.channel.sendMessage(role + ': message here');
    }, 1000*3600*48);
  }

  if (msg.content.startsWith(prefix + "help")) {
    msg.channel.sendMessage('');
  }

  if (msg.content.startsWith(prefix + "scrubnub")) {
    let user = msg.mentions.users.first();
    msg.channel.sendMessage(user + ' is a skkkrrruubbb');
  }
});

bot.on('error', e => { console.error(e); });

bot.login(token);