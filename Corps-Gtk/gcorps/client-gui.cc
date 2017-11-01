/*  Client GUI class for gcorps
    Copyright (C) 1998-99 Sebastian Rittau

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <string>
#if 0 //FIXME
#include <cstdlib>
#endif
#include <cstdio>
#include <cerrno>

#include <unistd.h>
#include <pthread.h>
#include <libintl.h>

#include <corps/exception.hh>
#include <corps/game-wrapper.hh>
#include <corps/gamelist-wrapper.hh>
#include <corps/orb.hh>
#include <corps/roleplaying.hh>

#include "client.hh"
#include "client-gui.hh"
#include "gamelist.hh"
#include "gui.hh"
#include "gui_busyreq.hh"
#include "gui_filereq.hh"
#include "gui_gamechooser.hh"
#include "gui_gamewindow.hh"
#include "gui_inputreqs.hh"
#include "gui_msgreqs.hh"


extern CORPS_ORB *orb;
extern GUI       *gui;



Client_GUI::Client_GUI(Client &parent) throw() :
  client(parent),
  game_win(0),
  playfield(),
  file_req(0),
  busy_req(0),
  gameid_req(0),
  gamelist_req(0)
{
  pthread_mutex_init(&connect_lock, 0);
  pthread_mutex_init(&requester_lock, 0);

  game_win = new GUI_GameWindow(playfield);

  connect_to_method(game_win->connect, this, &Client_GUI::init_connecting);
  connect_to_method(game_win->open, this, &Client_GUI::init_opening);
  connect_to_method(game_win->leave, this, &Client_GUI::leave);
  connect_to_method(game_win->delete_client, this, &Client_GUI::delete_client);

  connect_to_method(playfield.text_entered, this, &Client_GUI::init_print_to_game);
}


Client_GUI::~Client_GUI() throw()
{
  close_windows();

  pthread_mutex_destroy(&requester_lock);
  pthread_mutex_destroy(&connect_lock);
}


void Client_GUI::show() throw()
{
  game_win->show();
}


// it is save to call leave_game() even if we are not currently connected
// this returns false if leaving was not possible
bool Client_GUI::leave_game() throw()
{
  // FIXME: if currently connecting, prompt user if he really wants to leave

  //FIXME: inform client that game was left
  playfield.leave();
  game_win->connected(false);
  return true;
}


void Client_GUI::delete_client() throw()
{
  close_windows();
  client.delete_client();
}


void Client_GUI::close_windows() throw()
{
  if(game_win) { game_win->hide(); delete game_win; game_win = 0; }
  if(file_req) { file_req->hide(); delete file_req; file_req = 0; }
  if(busy_req) { busy_req->hide(); delete busy_req; busy_req = 0; }
  if(gameid_req) { gameid_req->hide(); delete gameid_req; gameid_req = 0; }
  if(gamelist_req) { gamelist_req->hide(); delete gamelist_req; gamelist_req = 0; }
}


struct print_to_game_args { Client_GUI *o; string s; };
void Client_GUI::init_print_to_game(string text) throw()
{
  pthread_t thread;
  print_to_game_args *args = new print_to_game_args;
  args->o = this;
  args->s = string(text);
  pthread_create(&thread, 0, &try_print_to_game, args);
  pthread_detach(thread);
}


void Client_GUI::print_to_game(string text) throw()
{
  try { client.print_to_game(text); }
  catch(Exception e) { GUI::exception(e); }
}


void *Client_GUI::try_print_to_game(void *s) throw()
{
  print_to_game_args *st = static_cast<print_to_game_args *>(s);
  st->o->print_to_game(st->s);
  delete st;
}

/**************************** connect methods ******************************/

void Client_GUI::init_connecting() throw()
{
  pthread_t thread;
  pthread_create(&thread, 0, &try_connect, this);
  pthread_detach(thread);
}


void Client_GUI::connect() throw()
{
  if(!leave_game())
    return;

  // we are nice - if somebody is currently connecting, we don't try to
  if(pthread_mutex_trylock(&connect_lock) == EBUSY)
    return;
  gui->lock(); game_win->connecting(true); gui->unlock();

  try
    {
      // get game or game list id
      pthread_mutex_lock(&requester_lock);
      gui->lock();
      gameid_req =
	new GUI_StringRequester(gettext("Choose Game or Game List"),
				gettext("Please enter the id of a Game or Game List:"),
				GUI_StringRequester::LAY_OKCANCEL);
      gameid_req->show();

      unsigned int c = gui->freelock();
      GUI_Requester::Action ret = gameid_req->wait_for_action();
      gui->relock(c);

      const string id = gameid_req->get_contents();
      gameid_req->hide(); delete gameid_req; gameid_req = 0;
      gui->unlock();
      pthread_mutex_unlock(&requester_lock);

      if(ret == GUI_StringRequester::ACTION_OK)
	{

	  bool do_connect = true;
	  Game_Wrapper game;

          CORBA::Object_var o;
          o = orb->string_to_object(id);
          RolePlaying::Game_var game_o = RolePlaying::Game::_narrow(o);
          if(CORBA::is_nil(game_o))
	    {
	      RolePlaying::GameList_var gl_o =
		RolePlaying::GameList::_narrow(o);
	      if(CORBA::is_nil(gl_o))
		{
		  //FIXME
		  return;
		}
	      GameList_Wrapper gamelist(gl_o);
	      Game_Wrapper *game_ptr = get_game_from_list(gamelist);
	      if(!game_ptr)
		do_connect = false;
	    }
	  else
	    game = Game_Wrapper(game_o);

	  // connect to that game
	  if(do_connect)
	    connect_to_game(game);
	}

    }
  catch(Exception e) { GUI::exception(e); }

  // clean up
  gui->lock(); game_win->connecting(false); gui->unlock();
  pthread_mutex_unlock(&connect_lock);
}


void *Client_GUI::try_connect(void *o) throw()
{
  static_cast<Client_GUI *>(o)->connect();
  return 0;
}


Game_Wrapper *Client_GUI::get_game_from_list(GameList_Wrapper &glw) throw(Exception)
{
  GameList gl = glw.get_list();
  if(gl.empty())
    throw Exception(gettext("Sorry, the list of games is empty."));

  // pop up game list requester
  pthread_mutex_lock(&requester_lock);
  gui->lock();
  GUI_GameChooser *gamelist_req = new GUI_GameChooser(gl);
  gamelist_req->show();

  // wait for user action ...
  unsigned int c = gui->freelock();
  GUI_Requester::Action ret = gamelist_req->wait_for_action();
  gui->relock(c);

  // ... and possibly get game from requester
  Game_Wrapper *game = 0;
  if(ret == GUI_GameChooser::ACTION_OK)
    {
      Game_Wrapper game_ref = gamelist_req->get_contents();
      game = new Game_Wrapper(game_ref);
    }

  // close requester
  gamelist_req->hide(); delete gamelist_req; gamelist_req = 0;
  gui->unlock();
  pthread_mutex_unlock(&requester_lock);

  // abort if requester was aborted
  if(ret != GUI_GameChooser::ACTION_OK)
    return 0;

  return game;
}

/****************************** game opening methods ***********************/

void Client_GUI::init_opening() throw()
{
  pthread_t thread;
  pthread_create(&thread, 0, &try_open, this);
  pthread_detach(thread);
}


void Client_GUI::open() throw()
{
  if(!leave_game())
    return;

  // we are nice - if somebody else is currently connecting, we don't try to
  if(pthread_mutex_trylock(&connect_lock) == EBUSY)
    return;
  gui->lock(); game_win->connecting(true); gui->unlock();

  string fn = request_game_filename();

  if(!fn.empty())
    connect_to_named_game(fn);

  // clean up
  gui->lock(); game_win->connecting(false); gui->unlock();
  pthread_mutex_unlock(&connect_lock);
}


void *Client_GUI::try_open(void *o) throw()
{
  static_cast<Client_GUI *>(o)->open();
  return 0;
}


string Client_GUI::request_game_filename() throw()
{
  string fn;

  pthread_mutex_lock(&requester_lock);

  {
    gui->lock();
    file_req = new GUI_FileRequester(gettext("Choose a game"));
    file_req->show();

    unsigned int c = gui->freelock();
    GUI_FileRequester::Action ret = file_req->wait_for_action();
    gui->relock(c);

    file_req->hide();
    fn = file_req->get_filename();
    delete file_req; file_req = 0;
    gui->unlock();

    if(ret != GUI_FileRequester::ACTION_OK)
      fn.erase();
  }

  pthread_mutex_unlock(&requester_lock);

  return fn;
}


// needed for busy requester
class MyNotify : public GUI_BusyRequester::Notify
{
public:
  MyNotify(_GameList &o) throw() : gl(o) {}
  virtual void notify() throw() { gl.abort(); }
private:
  _GameList &gl;
};

void Client_GUI::connect_to_named_game(const string &filename) throw()
{
  // gamelist-object must be created with "new" operator
  _GameList *gl = new _GameList;
  gl->_obj_is_ready(orb->getBOA());

  MyNotify notify_o(*gl);

  // run program
  switch(pid_t pid = vfork()) {
  case -1:
    notify_o.notify();
    GUI::exception(Exception(errno));
    gl->_dispose();
    return;
  case 0:
    {
      // find out basename of "filename"
      string progname = filename;
      string::size_type pos = progname.rfind('/');
      if(pos != -1) { progname.erase(0, pos + 1); }
      // try to execute program
      execl(filename.c_str(),                                            // prog
	    progname.c_str(), "-r", orb->object_to_string(gl).c_str(), 0 // args
	    );
      // an error occured
      //FIXME: notify parent process to cancel busy requester
      string err(gettext("Could not run adventure-file: "));
      err.append(sys_errlist[errno]);
      GUI::exception(Exception(err));
      _exit(1);
    }
  }

  // pop up busy-requester
  gui->lock();
  busy_req = new GUI_BusyRequester(gettext("Waiting..."),
				   gettext("Waiting for game to connect..."));
  busy_req->set_oncancel(notify_o);
  busy_req->show();
  gui->unlock();

  // wait for game to connect
  Game_Wrapper *game_ptr =
    gl->wait_for_registry(); // result will be a null pointer if waiting
                             // was aborted
  gl->_dispose();
  gui->lock(); busy_req->hide(); delete busy_req; busy_req = 0; gui->unlock();

  // connect to that game (if waiting was not aborted)
  if(game_ptr)
    {
      try { connect_to_game(*game_ptr); }
      catch(Exception e) { GUI::exception(e); }
      delete game_ptr;
    }
}

/**************************************************************************/

void Client_GUI::print_text(const string &text) throw()
{
  gui->lock();
  playfield.print_text(text);
  gui->unlock();
}


string Client_GUI::request_string(const string &what) throw()
{
  pthread_mutex_lock(&requester_lock);

  gui->lock();
  GUI_StringRequester *req = new GUI_StringRequester(gettext("Information Request"), what);
  req->show();

  unsigned int c = gui->freelock();
  req->wait_for_action();
  gui->relock(c);

  string s = req->get_contents();
  req->hide();
  delete req;
  gui->unlock();

  //FIXME: filter invalid characters

  pthread_mutex_unlock(&requester_lock);
  return s;
}


string Client_GUI::request_text(const string &what) throw()
{
  pthread_mutex_lock(&requester_lock);

  gui->lock();
  GUI_TextRequester *req = new GUI_TextRequester(gettext("Information Request"), what);
  req->show();
  gui->unlock();

  req->wait_for_action();

  gui->lock();
  string s = req->get_contents();
  req->hide();
  delete req;
  gui->unlock();

  //FIXME: filter invalid characters and reflow text

  pthread_mutex_unlock(&requester_lock);
  return s;
}


void Client_GUI::kick(const string &reason) throw()
{
  playfield.leave();

  GUI_MessageRequester *req =
    new GUI_MessageRequester(gettext("Game Quitted"),
			     gettext("The game has closed connection:"),
			     reason);
  req->handle_self_destruction();
  req->show();
}


void Client_GUI::connect_to_game(Game_Wrapper &game) throw(Exception)
{
  bool connect_successful = false;

  unsigned int c = gui->freelock();
  try { client.connect_to_game(game); }
  catch(...) { gui->relock(c); throw; }
  gui->relock(c);

  gui->lock();
  playfield.connect(game);
  game_win->connected(true);
  gui->unlock();
}
