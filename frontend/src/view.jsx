import React from "react";
import { BrowserRouter as Router, Routes, Link, Route } from 'react-router-dom';
import Login from "./components/Login";
import MainPage from "./components/MainPage";
import Header from "./components/layout/Header";
import Footer from "./components/layout/Footer";
import AuthUser from "./components/AuthUser";

const View = () => {
	return (
		<Router>
			<Header />
			<Routes>
				<Route path="/login" element={ <Login/> }/>
				<Route path="/auth-user" element={ <AuthUser />}/>
				<Route path="/main" element={ <MainPage/>}/>
			</Routes>
			<Footer />
		</Router>
	);
};

export default View;