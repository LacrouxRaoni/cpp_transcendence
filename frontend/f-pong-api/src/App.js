import './App.css';
import React from 'react';
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';
import Header from './components/Header'
import Footer from './components/Footer'
import Login from './components/Login'


function App() {
  return (
	<Router>
		<div>
			<Header/>
			<Routes>
				<Route path='/login' Component={ Login }/>
			</Routes>	
			<Footer/> 

		</div>
	</Router>
);
}

export default App;
